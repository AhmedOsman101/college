// deno-lint-ignore-file
import { markdownTable } from "markdown-table";

type LogicFn = (...args: boolean[]) => boolean;
type MultiLogicFn = (...args: boolean[]) => boolean[];
type Alignment = "l" | "c" | "r" | "";

type TruthTableResult<H extends readonly string[]> = {
  headers: H;
  columns: { [K in keyof H]: (number | boolean)[] };
  alignments?: Alignment[];
};

/* ---------------- Basic Gates ---------------- */
const and: LogicFn = (...args) => args.length > 0 && args.every(Boolean);

const or: LogicFn = (...args) => args.length > 0 && args.some(Boolean);

const not: LogicFn = a => !a;

/* ---------------- Derived Gates ---------------- */
const nand: LogicFn = (...args) => !and(...args);

const nor: LogicFn = (...args) => !or(...args);

const xor: LogicFn = (...args) => args.reduce((acc, cur) => acc !== cur, false);

const xnor: LogicFn = (...args) => !xor(...args);

/* ---------------- Helpers ---------------- */
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

function formatCell(value: number | boolean): string {
  if (typeof value === "boolean") return value ? "1" : "0";
  return String(value);
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

function generateHeadersMulti(terms: number, outputLabels: string[]): string[] {
  const headers: string[] = [];

  for (let i = 0; i < terms; i++) {
    headers.push(i < 26 ? String.fromCharCode(65 + i) : `A${i - 25}`);
  }

  return outputLabels.length > terms
    ? outputLabels
    : [...headers, ...outputLabels];
}

function normalizeAlignments(
  terms: number,
  alignments?: Alignment | Alignment[]
): Alignment[] {
  if (typeof alignments === "string") {
    return [alignments, alignments, alignments];
  }

  if (Array.isArray(alignments)) {
    if (alignments.length < terms) {
      const validAlign = alignments.find(x => x !== undefined) ?? "l";
      for (let i = 0; i < terms; i++) {
        if (!alignments[i]) alignments.push(validAlign);
      }
    }
    return alignments;
  }

  return ["", "", ""] as Alignment[];
}

/* ---------------- Main functions ---------------- */

function generateTruthTable<const H extends readonly string[]>(
  fn: LogicFn,
  terms: number,
  outputLabel = "F",
  alignments?: Alignment | Alignment[]
): TruthTableResult<H> {
  const columns = generateTruthTableColumns(fn, terms);
  const headers = generateHeaders(terms, outputLabel) as unknown as H;

  return {
    headers,
    columns: columns as any,
    alignments: normalizeAlignments(terms + 1, alignments),
  };
}

function generateTruthTableMulti<const H extends readonly string[]>(
  fn: MultiLogicFn,
  terms: number,
  outputLabels: string[],
  alignments?: Alignment[]
): TruthTableResult<H> {
  const columns = generateTruthTableColumnsMulti(fn, terms);
  const headers = generateHeadersMulti(terms, outputLabels) as unknown as H;

  return {
    headers,
    columns: columns as any,
    alignments: normalizeAlignments(terms + outputLabels.length, alignments),
  };
}

function toMarkdown<H extends readonly string[]>(table: TruthTableResult<H>) {
  // Convert column-major -> row-major
  const rows = table.columns[0].map((_, r) =>
    table.columns.map(col => formatCell(col[r]))
  );

  const allRows = [table.headers.map(h => String(h)), ...rows];

  return markdownTable(allRows, { align: table.alignments });
}

const xorTable = generateTruthTable(nand, 2, "$\\overline{A \\cdot B}$", "c");

console.log(toMarkdown(xorTable));

export {
  generateBinaryCases,
  generateTruthTableColumns,
  formatCell,
  generateTruthTableColumnsMulti,
  generateHeaders,
  generateHeadersMulti,
  generateTruthTable,
  generateTruthTableMulti,
  and,
  or,
  not,
  nand,
  nor,
  xor,
  xnor,
};
