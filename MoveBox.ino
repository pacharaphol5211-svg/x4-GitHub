void FSpin(int box, long encoderPlus, char spin) {
  if (box == 1) {
    FFe(150, 500 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 2) {
    FFe(150, 1100 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 3) {
    FFe(150, 1750 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 4) {
    FFe(150, 2400 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  }
}


void BSpin(int box, long encoderPlus, char spin) {
  if (box == 1) {
    BBe(150, 500 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 2) {
    BBe(150, 1100 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 3) {
    BBe(150, 1750 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  } else if (box == 4) {
    BBe(150, 2400 + (encoderPlus));
    if (spin == 'l') {
      SpinL();
    } else if (spin == 'r') {
      SpinR();
    }
  }
}

void FTurn(int box, long encoderPlus, char spin) {
  if (box == 1) {
    FFe(120, 100 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnL();
    } else if (spin == 'r') {
      TurnR();
    }
  } else if (box == 2) {
    FFe(120, 600 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnL();
    } else if (spin == 'r') {
      TurnR();
    }
  } else if (box == 3) {
    FFe(120, 1250 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnL();
    } else if (spin == 'r') {
      TurnR();
    }
  } else if (box == 4) {
    FFe(120, 1900 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnL();
    } else if (spin == 'r') {
      TurnR();
    }
  }
}

void BTurn(int box, long encoderPlus, char spin) {
  if (box == 1) {
    BBe(120, 100 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnBL();
    } else if (spin == 'r') {
      TurnBR();
    }
  } else if (box == 2) {
    BBe(120, 600 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnBL();
    } else if (spin == 'r') {
      TurnBR();
    }
  } else if (box == 3) {
    BBe(120, 1250 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnBL();
    } else if (spin == 'r') {
      TurnBR();
    }
  } else if (box == 4) {
    BBe(120, 1900 + (encoderPlus), 1);
    if (spin == 'l') {
      TurnBL();
    } else if (spin == 'r') {
      TurnBR();
    }
  }
}
