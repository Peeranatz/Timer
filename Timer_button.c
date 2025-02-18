#define ADC0_pin 36       // กำหนดให้ขา 36 เป็นขาอ่านค่าสัญญาณ Analog (ADC0)
hw_timer_t *timer = NULL; /* สร้างตัวแปรสำหรับเก็บข้อมูลของ Hardware Timer */
int led = 32;             /* กำหนดขา 32 ให้เป็นขาควบคุม LED */

// ฟังก์ชันนี้จะถูกเรียกโดย Timer Interrupt
// มีหน้าที่สลับสถานะของ LED (เปิด -> ปิด, ปิด -> เปิด)
void IRAM_ATTR onTimer()
{
    digitalWrite(led, !digitalRead(led)); // อ่านค่าปัจจุบันของ LED แล้วกลับค่า
}

void setup()
{
    pinMode(led, OUTPUT); // กำหนดให้ขา LED เป็นขาออก (Output)
    Serial.begin(115200); // เปิดใช้งาน Serial Monitor ที่ความเร็ว 115200 Baud

    /* ตั้งค่าให้ใช้ Timer ที่ 0 (ESP32 มี 4 ตัว) */
    /* ตั้งค่าหาร (prescaler) เป็น 80 ทำให้ 1 tick ใช้เวลา 1 ไมโครวินาที (us) */
    timer = timerBegin(0, 80, true); // Timer 0, หารด้วย 80, นับขึ้น (count up)

    /* ผูกฟังก์ชัน onTimer ให้ทำงานเมื่อ Timer ทำงาน */
    timerAttachInterrupt(timer, &onTimer, true);

    /* ตั้งค่าให้ Timer เรียกฟังก์ชัน onTimer ทุก ๆ 1 วินาที (1000000 ไมโครวินาที) */
    timerAlarmWrite(timer, 1000000, true);

    /* เริ่มทำงานของ Timer */
    timerAlarmEnable(timer);
}

// อ่านค่าจาก ADC และเปลี่ยนความเร็วกระพริบของ LED ตามค่าที่อ่านได้
void loop()
{
    int adcValue = analogRead(ADC0_pin); // อ่านค่าจากขา 36 (ADC0)
    Serial.println(adcValue);            // แสดงค่าที่อ่านได้บน Serial Monitor

    if (adcValue >= 4030 && adcValue <= 4037)
    {                                         // ถ้ากดปุ่ม S1
        timerAlarmWrite(timer, 250000, true); // ตั้งให้ LED กระพริบที่ความถี่ 2 Hz (2 ครั้งต่อวินาที)
    }
    else if (adcValue >= 3245 && adcValue <= 3264)
    {                                         // ถ้ากดปุ่ม S2
        timerAlarmWrite(timer, 100000, true); // ตั้งให้ LED กระพริบที่ความถี่ 5 Hz (5 ครั้งต่อวินาที)
    }
    else if (adcValue >= 2600 && adcValue <= 2625)
    {                                        // ถ้ากดปุ่ม S3
        timerAlarmWrite(timer, 50000, true); // ตั้งให้ LED กระพริบที่ความถี่ 10 Hz (10 ครั้งต่อวินาที)
    }
    else if (adcValue >= 1847 && adcValue <= 1862)
    {                                        // ถ้ากดปุ่ม S4
        timerAlarmWrite(timer, 20000, true); // ตั้งให้ LED กระพริบที่ความถี่ 25 Hz (25 ครั้งต่อวินาที)
    }
    else if (adcValue >= 1122 && adcValue <= 1165)
    {                                        // ถ้ากดปุ่ม S5
        timerAlarmWrite(timer, 16667, true); // ตั้งให้ LED กระพริบที่ความถี่ 30 Hz (30 ครั้งต่อวินาที)
    }
    else
    {                                          // ถ้าไม่กดปุ่มใด ๆ
        timerAlarmWrite(timer, 1000000, true); // ตั้งให้ LED กระพริบช้า (1 ครั้งต่อวินาที)
    }
}
