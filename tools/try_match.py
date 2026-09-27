#!/usr/bin/env python3
"""Compile a C file with the project toolchain and compare every function in it
byte-wise against SLUS_014.36, with relocated fields masked.

usage: tools/try_match.py draft.c [func ...]

CC1=bin/gcc-2.7.2-psx/cc1 selects the PsyQ toolchain, which builds without
the second CSE pass unless RERUN=1 (see PSYQ_RERUN_CSE in the Makefile). Like
the Makefile it then runs the patched cc1 from tools/patch_cc1.py
(STOCK_CC1=1 keeps the unpatched one).

Functions that differ are printed side by side (ours | original) with the
differing instructions marked with **.
"""
import sys,subprocess,struct,re,os,tempfile
from elftools.elf.elffile import ELFFile
D=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
exe=open(f'{D}/disks/us/SLUS_014.36','rb').read()[0x800:]
src=sys.argv[1]; want=set(sys.argv[2:])
w=os.path.join(tempfile.mkdtemp(prefix='try_match_'),'draft')
cc1=os.environ.get('CC1',f'{D}/bin/gcc-2.8.1-psx/cc1')
cflags=os.environ.get('CFLAGS','-O2 -G0 -fsigned-char -fno-builtin -fdollars-in-identifiers')
psyq='2.7.2' in cc1
if psyq and os.path.realpath(cc1)==os.path.realpath(f'{D}/bin/gcc-2.7.2-psx/cc1') and not os.environ.get('STOCK_CC1'):
    sys.path.insert(0,f'{D}/tools'); import patch_cc1; cc1=patch_cc1.ensure()  # what the Makefile uses
if psyq and not os.environ.get('RERUN'): cflags+=' -fno-rerun-cse-after-loop'
mflags=os.environ.get('MASPSXFLAGS','--aspsx-version=2.86'+(' --expand-div' if psyq else ''))
fl='-mhard-float' if psyq else '-msoft-float'  # FLOAT_ABI in the Makefile
post=f'| python3 {D}/tools/aspsx_reorder.py' if (psyq or os.environ.get('REORDER')) else ''
cmd=f"mipsel-linux-gnu-cpp -P -undef -D__GNUC__=2 -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -I{D}/include -I{D}/external/psyq_headers/psyq_lib47/include -DSKIP_ASM {src} > {w}.i && {cc1} -quiet -mips1 -mcpu=3000 -mgas {fl} -fgnu-linker -Wall -Wno-unused {cflags} -o {w}.s {w}.i && python3 {D}/external/maspsx/maspsx.py {mflags} < {w}.s {post} > {w}.ms.s && mipsel-linux-gnu-as -EL -march=r3000 -no-pad-sections -O1 -G0 -o {w}.o {w}.ms.s"
r=subprocess.run(cmd,shell=True,capture_output=True,text=True)
if r.returncode: print(r.stderr); sys.exit(1)
if r.stderr.strip(): print(r.stderr.strip())
e=ELFFile(open(w+'.o','rb'))
text=e.get_section_by_name('.text').data()
rel={}
rs=e.get_section_by_name('.rel.text')
if rs: rel={x['r_offset']:x for x in rs.iter_relocations()}
syms=sorted([(s['st_value'],s.name) for s in e.get_section_by_name('.symtab').iter_symbols() if s['st_info']['type']=='STT_FUNC'])
dis=subprocess.run(['mipsel-linux-gnu-objdump','-d','--no-show-raw-insn',w+'.o'],capture_output=True,text=True).stdout
mine={}
for l in dis.splitlines():
    m=re.match(r'\s+([0-9a-f]+):\s+(.*)',l)
    if m: mine[int(m.group(1),16)]=re.sub(r'\s+',' ',m.group(2)).strip()
for i,(off,name) in enumerate(syms):
    if want and name not in want: continue
    m=re.match(r'func_([0-9A-F]{8})',name)
    import glob
    asm=next(iter(glob.glob(f'{D}/asm/main/nonmatchings/**/{name}.s',recursive=True)),None)
    if asm is not None:
        t=open(asm).read()
    else:
        # already in C: take it from splat's full disassembly
        t=None
        for full in glob.glob(f'{D}/asm/main/**/*.s',recursive=True):
            if '/nonmatchings/' in full: continue
            ft=open(full).read()
            k=ft.find(f'nonmatching {name}, ')
            if k>=0:
                e=ft.find(f'endlabel {name}',k)
                t=ft[k:e]; break
        if t is None: print(name,'?'); continue
    size=int(re.search(r'nonmatching \w+, 0x([0-9A-F]+)',t).group(1),16)
    addr=int(re.search(r'glabel '+name+r'\n\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ',t).group(1),16)
    end=syms[i+1][0] if i+1<len(syms) else len(text)
    body=t[t.index('glabel '+name):] if 'glabel '+name in t else t
    tl=[re.sub(r'\s+',' ',re.sub(r'.*\*/\s+','',l)).strip() for l in body.splitlines() if re.match(r'\s+/\*',l)]
    nd=0; rows=[]
    for k in range(max(size,end-off)//4):
        o=off+4*k
        a=struct.unpack('<I',text[o:o+4])[0] if o<end else None
        b=struct.unpack('<I',exe[addr-0x80010000+4*k:][:4])[0] if 4*k<size else None
        if a is not None and b is not None and o in rel:
            mk=0xfc000000 if (a>>26) in (2,3) else 0xffff0000; a&=mk; b&=mk
        bad=a!=b; nd+=bad
        rows.append(f"{'**' if bad else '  '} {mine.get(o,'') if o<end else '':38s}| {tl[k] if k<len(tl) else ''}")
    print(f'{name}: {"MATCH" if nd==0 else str(nd)+" diffs"} (size {end-off:#x} vs {size:#x})')
    if nd: print('\n'.join(rows))
