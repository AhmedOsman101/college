<?php

echo '<table border="1" cellpadding="8" cellspacing="0">';

for ($i = 1; $i <= 7; $i++) {
  echo "<tr>";
  for ($j = 1; $j <= 7; $j++) {
    echo "<td>" . $i * $j . "</td>";
  }
  echo "</tr>";
}

echo "</table>";
