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
    const [A, B, C = 0] = row; // C defaults to 0 for the 2-input case
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

function and(a: boolean, b: boolean, c = true) {
  return a && b && c;
}

function or(a: boolean, b: boolean, c = false) {
  return a || b || c;
}

function not(a: boolean) {
  return !a;
}

function nand(a: boolean, b: boolean, c = true) {
  return not(and(a, b, c));
}

/* Truth tables */

// 3 inputs
generateTruthTable("A·B·C", and, true);
generateTruthTable("~(A·B·C)", nand, true);
generateTruthTable("A + B + C", or, true);

// 2 inputs
generateTruthTable("A·B", (a, b) => and(a, b), false);
generateTruthTable("A + B", (a, b) => or(a, b), false);
generateTruthTable("~(A·B)", (a, b) => nand(a, b), false);
