#include "lesson_state_2.h"
#include "client_socket.h"
#include "menu_state.h"
LessonState2::LessonState2(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	face.setTexture(this->game->texManager.getRef("Ross_Strip"));
	// face.setTextureRect(sf::IntRect(0, 0, 280, 304));
	textBubble.setTexture(this->game->texManager.getRef("text_bubble"));
	text.setFont(this->game->defaultFont);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
	// text.setString("This is a test string. \nLet's check for line breaks too. \nAnd maybe a third one.");

	face.setPosition(sf::Vector2f(10, this->game->window.getSize().y - face.getTextureRect().height - 10));
	textBubble.setPosition(sf::Vector2f(260, 500));
	text.setPosition(textBubble.getPosition().x + 90, textBubble.getPosition().y + 20);

	LessonState2::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	setupGui();
	dialogID = 0;

	faceAniHandler.frameSize = sf::IntRect(0, 0, 280, 304);
	faceAniHandler.addAnim(Animation(0, 3, 0.1f));
	faceAniHandler.update(0.0f);


	dialog.push_back(" Lesson 3: Binary Numbers");
	dialog.push_back(" Hello, and welcome back! Break out your calculators, 'cuz we're going \nto get technical today.");
	dialog.push_back(" We've learned about natural numbers and integers, so let's learn about \nhow computers represent them!");
	dialog.push_back(" Computers can only deal in electrical signals - on or off, true or false, \nlight or dark.");
	dialog.push_back(" Some very smart people came up with a way to represent big numbers as a \nseries of electrical signals, known as binary.");
	dialog.push_back(" Binary is written using only the numbers 1 and 0.");
	dialog.push_back(" How about take a look at some examples? Let's start with writing the \nnumber 1 in binary.");
	dialog.push_back(" 1 in binary is the exact same. Just 1. That was easy, wasn't it?");
	dialog.push_back(" Changing 2 to binary is a little trickier. Since we only have 1 and 0 to work \nwith, we have to carry the 1 over to the next digit, like if we added \n9 and 1 together.");
	dialog.push_back(" So 2 in decimal becomes 10.");
	dialog.push_back(" With 3, we just add 1 to that, so it becomes 11.");
	dialog.push_back(" And 4, we do the same thing we did with 2, and write to the next digit over, \nso it becomes 100.");
	dialog.push_back(" You can start to see a pattern here. Each digit of a binary number is 2 to \nsome power. The first digit is 0, the second is 1, the third is 2.");
	dialog.push_back(" You can make any number into a binary number by splitting it up into \npowers of 2 and adding them all together. Isn't that neat?");
	dialog.push_back(" Let's be brave and try a bigger number. How about 27?");
	dialog.push_back(" If we're thinking in powers of 2, then 27 is 16 + 8 + 2 + 1. So we write 1s \nin the proper places and get 11011.");
	dialog.push_back(" Like with anything else in life, you'll have to practice this to get the \nhang of it.");
	dialog.push_back(" But I know you can do it.");
	text.setString(dialog.at(dialogID));
}

void LessonState2::draw(const float dt)
{
	this->game->window.setView(this->view);

	// Make the window black
	this->game->window.clear(sf::Color::Black);

	// Render everything
	// this->game->window.draw(logo);
	// this->game->window.draw(face);

	this->faceAniHandler.changeAnim(0);


	/* Update the animation */
	this->faceAniHandler.update(dt);

	/* Update the sprite */
	this->face.setTextureRect(this->faceAniHandler.bounds);

	this->game->window.draw(face);
	this->game->window.draw(textBubble);
	this->game->window.draw(text);


	// Setup the gui and render it on top
	gui->draw();

	// Render anything special in the LessonData
	// lessonData.draw(dt);
	return;
}


void LessonState2::update(const float dt)
{
	// Update anything special in the lessonData
	// lessonData.update(dt);
}

void LessonState2::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			// If the user closes the window
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			// If the user presses any key
		case sf::Event::KeyPressed:
		{
			// If the key was the Esc key
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();

			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (dialogID < dialog.size()){
					ClientSocket::lesson_progress(sf::Uint64(3), sf::Uint64(dialogID + 1));
					nextDialog();
				}
				else{
					ClientSocket::quiz_score(sf::Uint64(1), sf::Uint64(1));
					this->game->popState();
					return;
				}
				break;

			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

				previousDialog();
				break;
			}

		}
		}
		gui->handleEvent(event);
	}

	// Handle the gui callbacks
	tgui::Callback callback;

	if (gui == nullptr) return;
	while (gui->pollCallback(callback))
	{
		// Make sure tha callback comes from the button
		if (callback.id == 1)
		{
			// For the back button
			// this->game->poppedState = true;
			// this->game->popState();
		}
	}

	return;
}

void LessonState2::setupGui() {
	// Create the log out button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(160, 40);
	button2->setPosition(this->game->window.getSize().x - button2->getSize().x - 10, 10);
	button2->setText("Back");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(1);

}

void LessonState2::nextDialog() {
	dialogID++;
	if (dialogID < dialog.size()) {
		text.setString(dialog.at(dialogID));
	}

}

void LessonState2::previousDialog() {
	dialogID--;
	if (dialogID > 0) {
		text.setString(dialog.at(dialogID));
	}
}