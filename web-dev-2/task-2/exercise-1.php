<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Task 2 - Exercise 1</title>
</head>
<body>
  <h1>Task 2 - Exercise 1</h1>
  <?php
  $weather = ["rain", "sunshine", "clouds", "hail", "sleet", "snow", "wind"];
  echo <<<EOF
  We've seen all kinds of weather this month. <br>
  At the beginning of the month, we had $weather[5] and $weather[6]. <br>
  Then came $weather[1] with a few $weather[2] and some $weather[0]. <br>
  At least we didn't get any $weather[3] or $weather[4].
  EOF;
  ?>
</body>
</html>
