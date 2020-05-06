class LedMatrix {
  private:
    uint8_t rows[2] = { 2, 3 };
    uint8_t cols[4] = { 5, 6, 9, 10 };
    int colBrightness[4] = { 0, 85, 171, 255 };
    uint8_t photoResistor = A1;
    bool lightsTurnedOn = false;

  public:
    LedMatrix() {}

    void setup() {
      pinMode(this->rows[0], OUTPUT);
      pinMode(this->rows[1], OUTPUT);
      for (uint8_t i = 0; i < 4; ++i)
        pinMode(this->cols[i], OUTPUT);
      pinMode(this->photoResistor, INPUT);
    }

    bool isNightOutside() {
      return analogRead(this->photoResistor) < 100;
    }

    bool isLightOn() {
      return this->lightsTurnedOn;
    }

    void turnLightsOn() {
      for (int x = 0; x < 512; ++x) {
        for (uint8_t i = 0; i < 2; ++i) {
          digitalWrite(this->rows[i], 1);
          for (uint8_t j = 0; j < 4; ++j) {
            int val = this->colBrightness[j] + x - 255;
            val = val < 0 ? 0 : val;
            val = val > 255 ? 255 : val;
            analogWrite(this->cols[j], val );
          }
          digitalWrite(this->rows[i], 0);
          delay(3);
        }
      }

      this->lightsTurnedOn = true;
    }

    void turnLightsOff() {
      for (int x = 511; x >= 0; --x) {
        for (uint8_t i = 0; i < 2; ++i) {
          digitalWrite(this->rows[i], 1);
          for (uint8_t j = 0; j < 4; ++j) {
            int val = this->colBrightness[j] + x - 255;
            val = val < 0 ? 0 : val;
            val = val > 255 ? 255 : val;
            analogWrite(this->cols[j], val );
          }
          digitalWrite(this->rows[i], 0);
          delay(3);
        }
      }

      this->lightsTurnedOn = false;
    }

};

LedMatrix ledMatrix;

void setup() {
  ledMatrix.setup();
}

void loop() {
  if (ledMatrix.isNightOutside() && !ledMatrix.isLightOn())
    ledMatrix.turnLightsOn();
  else if (!ledMatrix.isNightOutside() && ledMatrix.isLightOn())
    ledMatrix.turnLightsOff();
}
