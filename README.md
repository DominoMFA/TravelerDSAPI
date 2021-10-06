# TravelerDSAPI

The DSAPI filter handles event kFilterAuthenticate. It detects if user who is about to authenticate already enabled MFA protection and if so make own password validation using PasswordSecret. It's expected that database with name 2fa.nsf is located on the server in the root.

## How to compile project (DLL) for Windows using Visual Studio Code 2010.

Compiler command line used for the build

```
/I"C:\App\notesapi901\include" /Zi /nologo /W3 /WX- /O2 /Oi /GL 
/D "NT" /D "W32" /D "W64" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" 
/Gm- /EHsc /MT /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Fp"x64\Release\dsapistub1.pch" /Fa"x64\Release\" /Fo"x64\Release\" /Fd"x64\Release\vc100.pdb" 
/Gd /TC /errorReport:queue 
```

Linker command line used for the build:

```
/OUT:"..\Projects\dsapistub1\x64\Release\dsapistub1.dll" /INCREMENTAL:NO /NOLOGO /DLL "notes.lib" /MANIFEST /ManifestFile:"x64\Release\dsapistub1.dll.intermediate.manifest"
/ALLOWISOLATION /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /DEBUG /PDB:"..\Projects\dsapistub1\x64\Release\dsapistub1.pdb"
/SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /PGD:"..\Projects\dsapistub1\x64\Release\dsapistub1.pgd" /LTCG /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X64 /ERRORREPORT:QUEUE 
```

## How to compile project (SO) for Linux using gcc.

Compiler command line used for the build (that should produce a dsapistub1.o file)

```
gcc dsapistub1.c -I$LOTUS/notesapi/include -c -O -w  -m64 -DGCC3 -DGCC4 -fno-strict-aliasing -DGCC_LBLB_NOT_SUPPORTED -Wformat -Wall -Wcast-align 
-Wconversion  -DUNIX -DLINUX -DLINUX86 -DND64 -DW32 -DLINUX64 -DW -DLINUX86_64 -DDTRACE -DPTHREAD_KERNEL -D_REENTRANT -DUSE_THREADSAFE_INTERFACES 
-D_POSIX_THREAD_SAFE_FUNCTIONS  -DHANDLE_IS_32BITS -DHAS_IOCP -DHAS_BOOL -DHAS_DLOPEN -DUSE_PTHREAD_INTERFACES -DLARGE64_FILES -D_LARGEFILE_SOURCE 
-D_LARGEFILE64_SOURCE -DNDUNIX64 -DLONGIS64BIT -DPRODUCTION_VERSION -DOVERRIDEDEBUG  -fPIC
```

Linker command line used for the build (that should produce a libdsapistub1.so file):

```
gcc -m64 -DGCC3 -DGCC4 "$LOTUS/notes/latest/linux/libnotes.so" -fno-strict-aliasing -DGCC_LBLB_NOT_SUPPORTED -Wformat -Wall -Wcast-align -Wconversion 
-shared -fPIC -Wl,-Bsymbolic,--whole-archive,-znodefs,-ztext -Wl,--no-whole-archive -L$LOTUS/notesapi/lib/linux64 -L/lib64 
-ldl -lrt -lm -lstdc++ -L/lib64 -lpthread -lc -lresolv -lc dsapistub1.o -o libdsapistub1.so
```

*NOTE (for Linux)*
1. $LOTUS is an alias for executive directory of lotus notes (i.e. $LOTUS = /opt/lotus)
2. for Linux OS the final SO file should always start with LIB prefix, otherwise it will not work.

*debug mode*

add variable to notes.ini to enable log mode
mfa_debug = 1 
