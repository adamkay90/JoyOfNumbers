#include "lesson_state.h"

#include "lesson_natural_numbers.h"

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

	// lessonData = LessonNaturalNumbers(text);

	text.setString(lessonData.getDialog(dialogID));
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
			this->game->poppedState = true;
			this->game->popState();
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
	if (dialogID < lessonData.getDialogCount()) {
		dialogID++;
		text.setString(lessonData.getDialog(dialogID));
	}
}

void LessonState::previousDialog() {
	if (dialogID > 0) {
		dialogID--;
		text.setString(lessonData.getDialog(dialogID));
	}
}