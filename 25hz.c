hw_timer_t *timer = NULL; /* ตัวแปรสำหรับเก็บข้อมูลของ Hardware Timer */
int led = 32;             /* กำหนดขา LED ไว้ที่ขา 32 */

// ฟังก์ชันนี้จะถูกเรียกอัตโนมัติทุกครั้งที่ Timer ถึงเวลาที่ตั้งไว้
// โดยจะสลับสถานะของ LED (ถ้าเปิดอยู่จะปิด ถ้าปิดอยู่จะเปิด)
void IRAM_ATTR onTimer()
{
    digitalWrite(led, !digitalRead(led)); // เปลี่ยนสถานะของ LED
}

void setup()
{
    pinMode(led, OUTPUT); // ตั้งค่าขา LED เป็นขาออก (Output)

    /* สร้าง Timer โดยใช้ Timer ตัวที่ 0 (ESP32 มีทั้งหมด 4 ตัว) */
    /* ตั้งค่าหารสัญญาณนาฬิกาเป็น 80 ทำให้ 1 tick ใช้เวลา 1 ไมโครวินาที (us) */
    timer = timerBegin(0, 80, true); // ใช้ Timer 0, ตั้งค่าหารเป็น 80, และให้นับขึ้น (count up)

    /* เชื่อมฟังก์ชัน onTimer เข้ากับ Timer */
    timerAttachInterrupt(timer, &onTimer, true);

    /* ตั้งค่าให้ Timer เรียกฟังก์ชัน onTimer ทุก ๆ 20,000 ไมโครวินาที (0.02 วินาที) */
    /* 1 tick = 1 ไมโครวินาที (us) => 20000 ticks = 20000 us = 0.02 วินาที */
    timerAlarmWrite(timer, 20000, true); // ตั้งค่า Timer และให้ทำงานซ้ำ (true)

    /* เปิดใช้งาน Timer */
    timerAlarmEnable(timer);
}

void loop()
{
    // ไม่มีอะไรต้องทำใน loop เพราะการกระพริบ LED ถูกควบคุมโดย Timer
}
