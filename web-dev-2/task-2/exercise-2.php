<?php

$cities = [
  "Tokyo",
  "Mexico City",
  "New York City",
  "Mumbai",
  "Seoul",
  "Shanghai",
  "Lagos",
  "Buenos Aires",
  "Cairo",
  "London",
];

function printArray(array $arr): void {
  foreach ($arr as $idx => $value) {
    echo $value;
    if ($idx < sizeof($arr) - 1) echo ', ';
  }
}

function printArrayList(array $arr): void {
  echo "<ul>";
  foreach ($arr as $value) echo "<li>$value</li>";
  echo "</ul>";
}


printArray($cities);

sort($cities);
printArrayList($cities);

array_push($cities, 'Los Angeles', 'Calcutta', 'Osaka', 'Beijing');
sort($cities);
printArrayList($cities);
