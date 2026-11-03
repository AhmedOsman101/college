public class Time {
  private int hour;
  private int minute;
  private int second;

  public Time(int hour, int minute, int second) {
    this.hour = hour;
    this.minute = minute;
    this.second = second;
  }

  int getHour() {
    return this.hour;
  }
  void setHour(int value) {
    if (value < 0 || value > 23) return;
    this.hour = value;
  }
  int getMinute() {
    return this.minute;
  }
  void setMinute(int value) {
    if (value < 0 || value > 59) return;
    this.minute = value;
  }
  int getSecond() {
    return this.second;
  }
  void setSecond(int value) {
    if (value < 0 || value > 59) return;
    this.second = value;
  }

  void setTime(int hour, int minute, int second) {
    this.setHour(hour);
    this.setMinute(minute);
    this.setSecond(second);
  }

  Time nextSecond() {
    int second = this.getSecond(), minute = this.getMinute(), hour = this.getHour();
    second++;

    if (second == 60) {
      second = 0;
      minute++;
      if (minute == 60) {
        minute = 0;
        hour++;
        if (hour == 24) {
          hour = 0;
        }
      }
    }
    return new Time(hour, minute, second);
  }
  Time prevSecond() {
    int second = this.getSecond(), minute = this.getMinute(), hour = this.getHour();
    if (second == 0) {
      second = 59;
      if (minute == 0) {
        minute = 59;
        if (hour == 0) {
          hour = 23;
        } else hour--;
      } else minute--;
    } else second--;
    return new Time(hour, minute, second);
  }

  public void print() {
    System.out.printf(
      "Hour: %d, Minute: %d, Second: %d\n",
      this.getHour(),
      this.getMinute(),
      this.getSecond()
    );
  }

  public static void main(String args[]) {
    new Time(23, 59, 59).nextSecond().print();
    new Time(0, 0, 0).prevSecond().print();
    new Time(10, 10, 10).prevSecond().print();
  }
}
