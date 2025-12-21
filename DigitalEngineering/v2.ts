type LogicFn = (...args: boolean[]) => boolean;
type MultiLogicFn = (...args: boolean[]) => boolean[];

/* ---------------- Basic Gates ---------------- */

const and: LogicFn = (...args) => args.length > 0 && args.every(Boolean);

const or: LogicFn = (...args) => args.length > 0 && args.some(Boolean);

const not: LogicFn = a => !a;

/* ---------------- Derived Gates ---------------- */

const Nand: LogicFn = (...args) => !and(...args);

const nor: LogicFn = (...args) => !or(...args);

const xor: LogicFn = (...args) => args.reduce((acc, cur) => acc !== cur, false);

const xnor: LogicFn = (...args) => !xor(...args);

/* ----------------------------------------------- */

function generateBinaryCases(n: number): number[][] {
  const rows = 2 ** n;
  const cases: number[][] = [];

  for (let i = 0; i < rows; i++) {
    const row: number[] = [];
    for (let bit = n - 1; bit >= 0; bit--) {
      row.push((i >> bit) & 1);
    }
    cases.push(row);
  }

  return cases;
}

function generateTruthTableColumns(fn: LogicFn, terms: number): number[][] {
  const cases = generateBinaryCases(terms);

  const inputColumns: number[][] = Array.from({ length: terms }, () => []);

  const outputColumn: number[] = [];

  for (const row of cases) {
    row.map((value, i) => inputColumns[i].push(value));
    outputColumn.push(Number(fn(...row.map(Boolean))));
  }

  return [...inputColumns, outputColumn];
}

function generateTruthTableColumnsMulti(
  fn: MultiLogicFn,
  terms: number
): number[][] {
  const cases = generateBinaryCases(terms);

  const inputColumns: number[][] = Array.from({ length: terms }, () => []);

  let outputColumns: number[][] = [];

  for (const row of cases) {
    // push inputs
    row.map((value, i) => inputColumns[i].push(value));

    // evaluate outputs
    const outputs = fn(...row.map(Boolean));

    if (outputColumns.length === 0) {
      outputColumns = Array.from({ length: outputs.length }, () => []);
    }

    outputs.map((out, i) => outputColumns[i].push(Number(out)));
  }

  return [...inputColumns, ...outputColumns];
}

function generateHeaders(terms: number, outputLabel = "OUT"): string[] {
  const headers: string[] = [];

  for (let i = 0; i < terms; i++) {
    headers.push(i < 26 ? String.fromCharCode(65 + i) : `A${i - 25}`);
  }

  headers.push(outputLabel);
  return headers;
}

type Alignment = "left" | "center" | "right";

function genTableAdvanced(
  headers: any[],
  arrays: any[][],
  alignments?: Alignment[]
): string {
  const maxLength = Math.max(...arrays.map(arr => arr.length));
  const transposed: any[][] = [];

  for (let i = 0; i < maxLength; i++) {
    transposed[i] = arrays.map(col => (col[i] !== undefined ? col[i] : ""));
  }

  const alignmentChars = {
    left: ":--",
    center: ":-:",
    right: "--:",
  };

  let markdown = "";

  if (transposed.length > 0) {
    // Header row
    markdown += `| ${headers.join(" | ")} |\n`;

    // Separator row with alignment
    const defaultAlign = alignments || Array(arrays.length).fill("center");
    const separators = defaultAlign.map(
      (align: Alignment) => alignmentChars[align]
    );
    markdown += `| ${separators.join(" | ")} |\n`;

    // Data rows
    for (let i = 0; i < transposed.length; i++) {
      markdown += `| ${transposed[i].join(" | ")} |\n`;
    }
  }

  return markdown.trim();
}

function generateHeadersMulti(terms: number, outputLabels: string[]): string[] {
  const headers: string[] = [];

  for (let i = 0; i < terms; i++) {
    headers.push(i < 26 ? String.fromCharCode(65 + i) : `A${i - 25}`);
  }

  return outputLabels.length > terms
    ? outputLabels
    : [...headers, ...outputLabels];
}

function generateLogicTable(
  fn: LogicFn,
  terms: number,
  outputLabel = "F",
  alignments?: Alignment[]
): string {
  const columns = generateTruthTableColumns(fn, terms);
  const headers = generateHeaders(terms, outputLabel);

  return genTableAdvanced(headers, columns, alignments);
}

function generateLogicTableMulti(
  fn: MultiLogicFn,
  terms: number,
  outputLabels: string[],
  alignments?: Alignment[]
): string {
  const columns = generateTruthTableColumnsMulti(fn, terms);
  const headers = generateHeadersMulti(terms, outputLabels);

  return genTableAdvanced(headers, columns, alignments);
}

const res = generateLogicTableMulti(
  (control, a0, a1, b0, b1) => {
    // First half
    const xor1 = xor(b0, control);
    const xor2 = xor(a0, xor1);
    const and1 = and(a0, xor1);
    const and2 = and(control, xor2);

    const sum1 = xor(xor(control, xor2));
    const carry0 = or(and1, and2);

    // Second half
    const xor3 = xor(b1, control);
    const xor4 = xor(a1, xor3);
    const and3 = and(a1, xor3);
    const and4 = and(carry0, xor4);

    const sum2 = xor(carry0, xor4);
    const carry1 = or(and3, and4);

    return [sum1, sum2, carry1];
  },
  5,
  ["control", "a0", "a1", "b0", "b1", "sum1", "sum2", "carry"]
);

console.log(res);
