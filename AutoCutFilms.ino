int Counter_Sensor = 8; //to count the film`s length by perforations
int led = 13;           //show Counter_Sensor detected perforations ONBOARD_LED
int Cut = 5;            //Cut films
int Sensor_Counting = 0;// counting perforations  
int Counter_State = 0;  // counter current
int last_CounterSensor = 0;    // the last state of sensor
void setup() {
  // 设置sensor的针脚为输入状态
  pinMode(Counter_Sensor, INPUT);
  // 设置电路板上LED神灯的针脚状态为输出状态
  pinMode(led, OUTPUT);
  // 设置控制切刀的针脚状态为输出状态
  pinMode(Cut, OUTPUT);
  // 开启串行通信，并设置其频率为9600。
  // 如果没有特别要求，此数值一般都为9600。
  Serial.begin(9600);
}
// 系统调用，无限循环方法
void loop() {
  // 读取sensor的输入状态
  Counter_State = digitalRead(Counter_Sensor);
  // 判断当前的sensor状态是否和之前有所变化
  if (Counter_State != last_CounterSensor) {
    // 判断当前sensor是否为按下状态，
    // 如果为按下状态，则记录sensor次数的变量加一。
    if (Counter_State == HIGH) {
      // 将记录sensor次数的变量加一
      Sensor_Counting++;
      // 向串口调试终端打印字符串“on”，
      // 表示当前sensor状态为按下接通状态，
      // 输出完成之后自动换行。
      Serial.println("on");
      // 向串口调试终端打印字符串
      // “number of button pushes: ”，此处没有换行。
      Serial.print("number of button pushes:  ");
      // 接着上一行尾部，打印记录sensor次数变量的数值。
      Serial.println(Sensor_Counting);
    } else {
      // 向串口调试终端打印字符串“off”，
      // 表示当前sensor状态为松开状态，也即断开状态。
      Serial.println("off");
    }
    // 为了避免信号互相干扰，
    // 此处将每次sensor的变化时间间隔延迟50毫秒。此处依据胶片速度也会有问题！！！
    delay(50);
  }
  // 将每次loop结束时最新的sensor状态进行更新
  last_CounterSensor = Counter_State;
  // 每点击10次，更新一次LED神灯状态。
  // 这里的百分号是求余数的意思，
  // 每次除以10，余数等于零说明sensor点击的
  // 次数是四的整数倍，即此时更新LED神灯。刚好是一张135的长度
  if (Sensor_Counting % 10 == 0) {
    // 点亮LED神灯
    digitalWrite(ledPin, HIGH);
    //具体延迟时间需要调试！！！！！！
    delay(); 
    digitalWrite(Cut,HIGH);
  } else {
    // 熄灭LED神灯
    digitalWrite(ledPin, LOW);
  }
}