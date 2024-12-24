<?php

declare(strict_types=1);

$char2index = fn($char): int => ord($char) - 97;
$index2char = fn($index): string => chr($index + 97);

$E = [
  [3, 6],
  [1, 5],
];

$E_inverse = [
  [15, 8],
  [23, 9],
];

function multiplyMatrices(array $A, array $B): array {
  $result = [];

  for ($i = 0; $i < sizeof($A); $i++) {
    $row = $A[$i];

    for ($j = 0; $j < sizeof($B[0]); $j++) {
      $col = array_column($B, $j);
      @$result[$i][$j] += ($row[0] * $col[0]) + ($row[1] * $col[1]);
    }
  }

  return $result;
}

function encrypt(string $text): string {
  global $char2index, $index2char, $E;

  $P = [
    [],
    [],
  ];

  for ($i = 0; $i < strlen($text); $i++) {
    $char = $text[$i];
    $i % 2 == 0 ? $P[0][] = $char2index($char) : $P[1][] = $char2index($char);
  }



  $Q = multiplyMatrices($E, $P);
  $encryptedString = "";

  foreach ($Q as &$row) {
    foreach ($row as &$cell) {
      $cell %= 26;
    }
  }

  for ($i = 0; $i < sizeof($Q[0]); $i++) {
    $col = array_column($Q, $i);
    $encryptedString .= $index2char($col[0]);
    $encryptedString .= $index2char($col[1]);
  }

  return $encryptedString;
}

function decrypt(string $text): string {
  global $char2index, $index2char, $E_inverse;

  $Q = [];

  for ($i = 0; $i < strlen($text); $i++) {
    $char = $text[$i];
    $i % 2 == 0 ? $Q[0][] = $char2index($char) : $Q[1][] = $char2index($char);
  }



  $P = multiplyMatrices($E_inverse, $Q);
  $decryptedString = "";

  foreach ($P as &$row) {
    foreach ($row as &$cell) {
      $cell %= 26;
    }
  }

  for ($i = 0; $i < sizeof($P[0]); $i++) {
    $col = array_column($P, $i);
    $decryptedString .= $index2char($col[0]);
    $decryptedString .= $index2char($col[1]);
  }

  return $decryptedString;
}

function main(): void {
  echo "Enter any text: ";
  $text = str_replace(" ", "", strtolower(trim(fgets(STDIN))));

  echo "Type E to encrypt or D to decrypt (D/E) ";
  $operation = strtoupper(trim(fgets(STDIN)));

  $result = $operation == 'E' ? encrypt($text) : decrypt($text);

  var_dump($result);
}

main();

echo PHP_EOL;
