#include "lesson_state_1.h"
#include "client_socket.h"
#include "menu_state.h"

LessonState1::LessonState1(Game* game) {
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

	LessonState1::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	setupGui();
	dialogID = 0;

	faceAniHandler.frameSize = sf::IntRect(0, 0, 280, 304);
	faceAniHandler.addAnim(Animation(0, 3, 0.1f));
	faceAniHandler.update(0.0f);

	dialog.push_back("Hi there. So glad to see you again. Today I've got something really \nneat to teach you about.");
	dialog.push_back("Today we're going to talk about integers!");
	dialog.push_back("If you remember from last time, natural numbers are numbers that \nyou can count on your fingers and toes... if you had enough fingers\nand toes, of course.");
	dialog.push_back("Integers include all the natural numbers, but they also include all \nthe negative numbers, too.");
	dialog.push_back("Now what on earth's a negative number? It's not really something \nyou can count on your fingers, after all.");
	dialog.push_back("Think of negative numbers like debt. Having a negative number is like \nhaving debt, you have an absence of some number.");
	dialog.push_back("Trust me, I'm no stranger to having debt. It used to be that it was rare \nthat I had a happy little buck in my pocket, haha.");
	dialog.push_back("Anyway, integers are just all the positive numbers, all the negative \nnumbers, and zero, too.");
	dialog.push_back("Make sure to keep in mind that -100 is a smaller number than -10, \nwhich is a smaller number than 0.");
	dialog.push_back("We can also negate any number. The negation of a negative number is a\npositive number, and the negation of a postive number is a negative\none.");
	dialog.push_back("You can try to negate zero all you want, but it'll stay zero.");
	dialog.push_back("Hmm, that's about all I can think of to explain about integers. That \nwasn't so bad, was it?");
	dialog.push_back("I really enjoyed having you here with me today, and I hope to see \nyou again soon.");

	text.setString(dialog.at(dialogID));
}

void LessonState1::draw(const float dt)
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


void LessonState1::update(const float dt)
{
	// Update anything special in the lessonData
	// lessonData.update(dt);
}

void LessonState1::handleInput()
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
					ClientSocket::lesson_progress(sf::Uint64(2), sf::Uint64(dialogID + 1));
					nextDialog();
				}
				else{
					ClientSocket::lesson_progress(sf::Uint64(3), sf::Uint64(1));
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

void LessonState1::setupGui() {
	// Create the log out button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(160, 40);
	button2->setPosition(this->game->window.getSize().x - button2->getSize().x - 10, 10);
	button2->setText("Back");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(1);

}

void LessonState1::nextDialog() {
	dialogID++;
	if (dialogID < dialog.size()) {
		text.setString(dialog.at(dialogID));
	}

}

void LessonState1::previousDialog() {
	dialogID--;
	if (dialogID > 0) {
		text.setString(dialog.at(dialogID));
	}
}