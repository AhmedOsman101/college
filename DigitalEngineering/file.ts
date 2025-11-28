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

/* Truth tables */

// 3 inputs
// generateTruthTable("A·B·C", and, true);
// generateTruthTable("~(A·B·C)", nand, true);
// generateTruthTable("A + B + C", or, true);

// 2 inputs
// generateTruthTable("A·B", (a, b) => and(a, b), false);
// generateTruthTable("A + B", (a, b) => or(a, b), false);
// generateTruthTable("~(A·B)", (a, b) => nand(a, b), false);
// generateTruthTable("A·B", (a, b) => nand(nand(a, b), nand(a, b)), false);
// generateTruthTable("A+B", (a, b) => nand(nand(a, a), nand(b, b)), false);

generateTruthTable(
  "~A~B",
  (a, b) =>
    nand(nand(nand(a, a), nand(b, b)), nand(nand(a, a), nand(b, b))),
  false
);
// generateTruthTable(
//   "~A~BC",
//   (a, b, c) =>
//     nand(nand(nand(a, a), nand(b, b)), nand(nand(a, a), nand(b, b)), c),
//   true
// );

generateTruthTable(
  "AB + ~A~BC",
  (a, b, c) => {
    const notA = nand(a, a);
    const notB = nand(b, b);
    const notAnotBC = nand(notA, notB, c);
    const nandAB = nand(a, b);
    const AB = nand(nandAB, nandAB);
    const notABC = nand(notAnotBC, notAnotBC);
    const notAB = nand(AB, AB);
    const notNotABC = nand(notABC, notABC);
    return nand(notAB, notNotABC);
  },
  true
);

// Actual circuit
// generateTruthTable(
//   "F",
//   (a, b, c) => or(and(not(a), not(b), c), and(a, b)),
//   false
// );

// generateTruthTable(
//   "F",
//   (A, B, C) => {
//     const ABnot = nand(
//       nand(nand(A, A), nand(B, B)),
//       nand(nand(A, A), nand(B, B))
//     );

//     const LHS = nand(nand(A, B), nand(A, B));

//     const RHS = nand(ABnot, C as boolean);

//     const result = nand(nand(LHS, LHS), nand(RHS, RHS));
//     return result;
//   },
//   true
// );
