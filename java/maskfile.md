# Java Project

## build (file)

> Compile a single Java file

```bash
set -e
outDir="out"
mkdir -p "${outDir}"
javac -d "${outDir}" "src/${file}.java"
```

## run (file)

> Compile and run a single Java file

```bash
set -e
mask build "${file}"
className="${file^}"
java -cp "out" "${className}"
```

## build-all

> Compile all Java files in src/

```bash
set -e
outDir="out"
mkdir -p "${outDir}"
javac -d "${outDir}" src/*.java
```

## run-all

> Compile all and run Main

```bash
mask build-all
java -cp "out" Main
```
