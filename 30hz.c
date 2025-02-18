hw_timer_t *timer = NULL; /* ตัวแปรเก็บข้อมูลของ Hardware Timer */
int led = 32;             /* ใช้ขา 32 ควบคุม LED */

// ฟังก์ชันนี้จะถูกเรียกทุกครั้งที่ Timer ทำงานตามเวลาที่กำหนดไว้
// โดยจะสลับสถานะของ LED เปิด/ปิด สลับกัน
void IRAM_ATTR onTimer()
{
    digitalWrite(led, !digitalRead(led)); // อ่านสถานะ LED แล้วกลับค่า (ถ้าเปิดอยู่ให้ปิด ถ้าปิดอยู่ให้เปิด)
}

void setup()
{
    pinMode(led, OUTPUT); // ตั้งค่าขา LED เป็นขาออก (Output)

    /* ใช้ Timer ตัวที่ 0 (ESP32 มี 4 ตัว) */
    /* ตั้งค่าหาร (prescaler) เป็น 80 ทำให้ 1 tick ใช้เวลา 1 ไมโครวินาที (us) */
    timer = timerBegin(0, 80, true); // Timer 0, หารด้วย 80, นับขึ้น (count up)

    /* ผูกฟังก์ชัน onTimer กับ Timer */
    timerAttachInterrupt(timer, &onTimer, true);

    /* ตั้งค่าให้ Timer เรียกฟังก์ชัน onTimer ทุก ๆ 16,666 ไมโครวินาที (0.0167 วินาที) */
    /* 1 tick = 1 ไมโครวินาที => 16666 ticks = 16,666 ไมโครวินาที */
    timerAlarmWrite(timer, 16666, true); // ตั้งเวลาและให้ทำงานซ้ำ (true)

    /* เริ่มทำงานของ Timer */
    timerAlarmEnable(timer);
}

void loop()
{
    // วนลูปหลัก แต่ไม่มีโค้ดเพราะใช้ Timer จัดการทั้งหมดแล้ว
}
