#include "lesson_state.h"

LessonState::LessonState(Game* game) {
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

	LessonState::gui = new tgui::Gui(this->game->window);
	gui->setGlobalFont("media/arial.ttf");

	setupGui();
	dialogID = 0;

	faceAniHandler.frameSize = sf::IntRect(0, 0, 280, 304);
	faceAniHandler.addAnim(Animation(0, 3, 0.1f));
	faceAniHandler.update(0.0f);

		dialog.push_back("Hi, and welcome to the Joy of Numbers. I'm your host, Bob Ross. \nI'm so glad you could join me today to learn about one of life's most\nfascinating topics.");
		dialog.push_back("Today, we're going to talk about natural numbers. You probably\nknow a lot about natural numbers already, and you don't even know it yet.");
		dialog.push_back("Let's get started, shall we?");
		dialog.push_back("Natural numbers are, to put it simply, numbers you can count on your\nfingers and toes. One, two, three, those are all natural numbers.");
		dialog.push_back("Of course, we can't forget little old zero! That's a natural number too.");
		dialog.push_back("Every natural number is followed by another natural number. 1 is\nfollowed by 2, 100 is followed by 101. This goes on and on.");
		dialog.push_back("Since zero is the smallest of the natural numbers, it doesn't \nfollow any other natural number. It's at the front of the line.");
		dialog.push_back("If we have two natural numbers, but we don't know anything about\nthem except that they are the followed by the same number, then\nwe can conclude that they're the same natural number.");
		dialog.push_back("It sounds a bit more complicated then it actually is, haha.");
		dialog.push_back("If we have any group of natural numbers together, then we also\nknow that the group has a smallest natural number.");
		dialog.push_back("For example, if we have a set with the numbers 5, 9, and 12 in\nit, then we know 5 is the smallest number.");
		dialog.push_back("You might be thinking, \"Bob, if sets always have a smallest\nnumber, then surely they also have a largest number too!\"");
		dialog.push_back("But a set can have an infinite amount of natural numbers in it,\nand you can't have a biggest number from an infinite amount of numbers.");
		dialog.push_back("Now maybe you're thinking, \"Shucks, Bob, you got me. But why do\nI need to know this stuff anyway?\" Well, that's cause it's an important\nrule of natural numbers.");
		dialog.push_back("Mathematicians need all sorts of rules about numbers to be able\nto do stuff with them, even if they sound obvious to us.");
		dialog.push_back("If we didn't have those rules, we would have never been able to\nget to the moon and see the Earth in all its glory.");
		dialog.push_back("Oh, but I'm rambling again. I hope you enjoyed learning about\nnatural numbers, and I hope I see you again soon in the next lesson.");

	text.setString(dialog.at(dialogID));
}

void LessonState::draw(const float dt)
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


void LessonState::update(const float dt)
{
	// Update anything special in the lessonData
	// lessonData.update(dt);
}

void LessonState::handleInput()
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

					nextDialog();
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

void LessonState::setupGui() {
	// Create the log out button
	tgui::Button::Ptr button2(*gui);
	button2->load("TGUI-0.6/widgets/Black.conf");
	button2->setSize(160, 40);
	button2->setPosition(this->game->window.getSize().x - button2->getSize().x - 10, 10);
	button2->setText("Back");
	button2->bindCallback(tgui::Button::LeftMouseClicked);
	button2->setCallbackId(1);

}

void LessonState::nextDialog() {
	dialogID++;
	if (dialogID < dialog.size()) {
		text.setString(dialog.at(dialogID));
	}

}

void LessonState::previousDialog() {
	dialogID--;
	if (dialogID > 0) {
		text.setString(dialog.at(dialogID));
	}
}