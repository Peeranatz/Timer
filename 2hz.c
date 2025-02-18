hw_timer_t *timer = NULL; /* สร้างตัวแปรสำหรับตัวจับเวลา (Hardware Timer) */
int led = 32;             /* กำหนดขา (Pin) ที่ใช้ควบคุม LED เป็นขา 32 */

// ฟังก์ชันที่ทำงานเมื่อ Timer ถึงเวลาที่กำหนด (ต้องอยู่ใน IRAM)
void IRAM_ATTR onTimer()
{
  digitalWrite(led, !digitalRead(led)); // สลับสถานะของ LED (เปิด -> ปิด, ปิด -> เปิด)
}

void setup()
{
  pinMode(led, OUTPUT); // ตั้งค่าขา LED เป็นขาออก (Output)

  /* สร้างตัวจับเวลา (ใช้ Timer ตัวที่ 1 จากทั้งหมด 4 ตัว) */
  /* ตั้งค่าให้ 1 tick ใช้เวลา 1/(80MHz/80) = 1 ไมโครวินาที (us) */
  timer = timerBegin(0, 80, true); // ใช้ Timer 0, ตั้งค่าหารสัญญาณนาฬิกาเป็น 80, นับขึ้น (count up)

  /* ผูกฟังก์ชัน onTimer เข้ากับตัวจับเวลา */
  timerAttachInterrupt(timer, &onTimer, true);

  /* ตั้งค่าให้ตัวจับเวลาเรียก onTimer ทุก ๆ 250,000 ไมโครวินาที (หรือ 0.25 วินาที) */
  /* ค่า 1 tick = 1 ไมโครวินาที (us) => 250000 ticks = 250000 us = 0.25 วินาที */
  timerAlarmWrite(timer, 250000, true); // กำหนดค่า Timer และให้ทำงานซ้ำ (true)

  /* เปิดใช้งาน Timer */
  timerAlarmEnable(timer);
}

void loop()
{
  // ไม่มีอะไรต้องทำใน loop เพราะการกระพริบ LED ถูกควบคุมโดย Timer
}
