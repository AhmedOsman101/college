type LogicFn = (a: boolean, b: boolean, c?: boolean) => boolean;

function generateTruthTable(
  label: string,
  callback: LogicFn,
  threeInputs: boolean
) {
  const cases2 = [
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1],
  ];

  const cases3 = [
    [0, 0, 0],
    [0, 0, 1],
    [0, 1, 0],
    [0, 1, 1],
    [1, 0, 0],
    [1, 0, 1],
    [1, 1, 0],
    [1, 1, 1],
  ];

  const rows = threeInputs ? cases3 : cases2;

  const results = rows.map(row => {
    const [A, B, C] = row;
    if (threeInputs) {
      return {
        A,
        B,
        C,
        [label]: callback(!!A, !!B, !!C),
      };
    }

    return {
      A,
      B,
      [label]: callback(!!A, !!B),
    };
  });

  console.table(results);
}

/* ------------------------------------------------------- */
/* Example usage exactly like your original logic functions */

function and(a: boolean, b: boolean, c?: boolean) {
  if (c === undefined) {
    return a && b;
  }
  return a && b && c;
}

function or(a: boolean, b: boolean, c?: boolean) {
  if (c === undefined) {
    return a || b;
  }
  return a || b || c;
}

function not(a: boolean) {
  return !a;
}

function nand(a: boolean, b: boolean, c?: boolean) {
  if (c === undefined) {
    return not(and(a, b));
  }
  return not(and(a, b, c));
}

function generateCases(n: number) {
  const cases: number[][] = [];
  for (let i = 0; i < n; i++) cases.push([]);

  const numOfRows = 2 ** n; // 2^2 = 4
  for (let i = 0; i < n; i++) {
    let current = true;
    for (let j = 0; j < numOfRows; j++) {
      const currentRowNum = 2 ** i;
      if (j % currentRowNum === 0 || currentRowNum === 1) current = !current;
      cases[n - (i + 1)][j] = Number(current);
    }
  }

  return cases;
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

console.log(genTableAdvanced(["A", "B"], generateCases(2)));
console.log("-----------------------------------------------------");
console.log(genTableAdvanced(["A", "B", "C"], generateCases(3)));
console.log("-----------------------------------------------------");
console.log(genTableAdvanced(["Control", "A0", "A1", "B0", "B1"], generateCases(5)));
