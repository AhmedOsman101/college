# Java Project

## build (path)

> Compile a Java file or all files in a directory

```bash
set -e
outDir="out"
mkdir -p "${outDir}"
# If path ends with .java, compile that file; otherwise compile all .java files in the directory
if [[ "${path}" == *.java ]]; then
  javac -d "${outDir}" "src/${path}"
elif [[ -d "src/${path}" ]]; then
  javac -d "${outDir}" src/${path}/*.java
else
  echo "error: no such file or directory: src/${path}" >&2
  exit 1
fi
```

## run (path)

> Compile and run a Java file

```bash
set -e
# If the file lives in a subdirectory, compile the whole directory so its sibling classes are available
if [[ "${path}" == */* ]]; then
  $MASK build "$(dirname "${path}")"
else
  $MASK build "${path}"
fi
className=$(basename "${path}" .java)
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
$MASK build-all
java -cp "out" Main
```
