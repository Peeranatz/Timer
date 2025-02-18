hw_timer_t *timer = NULL; /* สร้างตัวแปรสำหรับเก็บข้อมูลของ Hardware Timer */
int led = 32;             /* กำหนดขา (Pin) ที่ใช้ควบคุม LED เป็นขา 32 */

// ฟังก์ชันนี้จะทำงานทุกครั้งที่ Timer ถึงเวลาที่ตั้งไว้
// โดยจะสลับสถานะของ LED (ถ้าติดก็ปิด ถ้าปิดก็ติด)
void IRAM_ATTR onTimer()
{
    digitalWrite(led, !digitalRead(led)); // สลับสถานะของ LED
}

void setup()
{
    pinMode(led, OUTPUT); // ตั้งค่าขา LED เป็นขาออก (Output)

    /* สร้าง Timer โดยใช้ตัวที่ 0 (ESP32 มีทั้งหมด 4 ตัว) */
    /* ตั้งค่าหารสัญญาณนาฬิกาเป็น 80 ทำให้ 1 tick ใช้เวลา 1 ไมโครวินาที (us) */
    timer = timerBegin(0, 80, true); // ใช้ Timer 0, ตั้งค่าหารสัญญาณนาฬิกาเป็น 80, นับขึ้น (count up)

    /* เชื่อมฟังก์ชัน onTimer เข้ากับ Timer */
    timerAttachInterrupt(timer, &onTimer, true);

    /* ตั้งค่าให้ตัวจับเวลาเรียก onTimer ทุก ๆ 100,000 ไมโครวินาที (0.1 วินาที) */
    /* ค่า 1 tick = 1 ไมโครวินาที (us) => 100000 ticks = 100000 us = 0.1 วินาที */
    timerAlarmWrite(timer, 100000, true); // ตั้งค่า Timer และให้ทำงานซ้ำ (true)

    /* เปิดใช้งาน Timer */
    timerAlarmEnable(timer);
}

void loop()
{
    // ไม่มีอะไรต้องทำใน loop เพราะการกระพริบ LED ถูกควบคุมโดย Timer
}
