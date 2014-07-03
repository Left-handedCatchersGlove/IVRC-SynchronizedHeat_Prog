int analogPin = 0;     // ポテンショメータのワイプ(中央の端子)に
                       // 両端はグランドと+5Vに接続
int val = 0;           // 読み取った値を格納する変数

void setup() {
  Serial.begin(9600); // シリアルポートを9600bpsで開く
}

void loop() {
  val = analogRead(analogPin);    // アナログピンを読み取る
  //Serial.write(val);            // デバグ用に送信
  //val = val >> 2;
  Serial.write(val);
  delay(50);
}

