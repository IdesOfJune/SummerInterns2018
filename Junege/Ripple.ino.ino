Color colors[] = {RED, ORANGE, YELLOW, GREEN };
byte currentColorIndex = 0;
bool colorChange = false;
byte sendValue = 0;
bool changeColorNeighbor = false;
bool canChange = false;

enum gameState {
  REST,
  ADVANCE,
  COMPLETE
};

byte gameState;

void setup() {
  gameState = REST;
}

void loop() {

  //button handling
  //single click advances self and notifies neighbors to advance themselves
  if ( buttonSingleClicked() ) {
    currentColorIndex++;
  }

  if (currentColorIndex >= COUNT_OF(colors)) {
    currentColorIndex = 0;
  }

  //update gamestate
  switch (gameState) {
    case REST:
      updateRest();
      break;
    case ADVANCE :
      updateAdvance();
      break;
    case COMPLETE:
      updateComplete();
      break;
  }
  //look at neighbors and if neighbor says to advance, advance self and change game state to advance completed
  //display gamestate
  switch (gameState) {
    case REST:
      displayRest();
      break;
    case ADVANCE :
      displayAdvance();
      break;
    case COMPLETE:
      displayComplete();
      break;
  }
  //send gamestate

  FOREACH_FACE(f) {
    if (!isValueReceivedOnFaceExpired(f)) {
      if (getLastValueReceivedOnFace(f) == 1 && canChange == false) {
        changeColorNeighbor = true;
        canChange = true;
      }
      if (getLastValueReceivedOnFace(f) == 0) {
        canChange = false;
      }
    }
  }

  if (changeColorNeighbor == true) {
    currentColorIndex++;
    changeColorNeighbor = false;

  }

  setValueSentOnAllFaces(sendValue);

  // display color
  setColor( colors[currentColorIndex] );


} //end of loop




