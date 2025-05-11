#include "Npc.h"
#include <iostream>

int Npc::CurrentInteraction = 0;
int Npc::currentLine = 0;
int Npc::inputDelay = 0;
sf::String Npc::voiceLines[41] = { L"Aubrey：助けてください！", //1 0

L"Aubrey：ゾンビたちは私たちを\n驚かしました。",
L"Aeryk：ゾンビが多過ぎます。",
L"Aubrey：こちらはだめです。",
L"Aeryk：私たちを助けてくれるなら、\n私は転石が押せます。",
L"Aeryk：行きましょう！", //5 5

L"Aubrey：私たちははしを渡りたいなら、\nはしを直さなければなりません。",
L"Aeryk：うん、そうね、\n誰が橋を直せるでしょう。", //2 7

L"Rowan：誰ですか？！\nゾンビは帰ってくれませんか。\n私はおいしくない。", //1 8

L"Rowan：あ、人間か。\nどうやって、生き残りましたか。",
L"Aubrey：フェニックスは\n助けてくれました。",
L"Aeryk：うん、どうやって、\nあなたは生き残りましたか。",
L"Rowan：うちに入って、待ちました。",
L"Aubrey：そうですか。",
L"Rowan：ところで、\n私のマジックブックを無くしました。\nこの町の南にあるでしょう。",
L"Rowan：ゾンビがいるから、あの町から\n逃（に）げなければなりませんでした。",
L"Rowan：私のマジックブックを\n持っていると、ゾンビと戦えます。",
L"Aeryk：そうですか、私たちはあの町を調べます。", //9 17

L"Aubrey：あ、マジックブックを\n見つけました。",
L"Aeryk：ローワンと一緒に\nあのゾンビたちを殺せるかもしれません。",
L"Aubrey：うん、そうですね", //3 20

L"Rowan：ありがとうございます！\n今からゾンビと戦えます。",//1 21

L"Aeryk：あぁ、あの人はやばいです。",
L"Aubrey：うん、\n私たちは助けたほうがいいです。", //2 23

L"Cal：どうも有難うございます！\n助けてくれなかったら、死んだでしょう。\n私は何で礼をできますか。",
L"Rowan：橋を直せますか？",
L"Cal：うん、橋を直せます。\nでも、どうして、橋を渡りたいですか。",
L"Aubrey：最初にゾンビは\nあそこから来たと思うから。",
L"Cal：そうですか。それから、\n私は助けてゾンビのリーダーを殺せます。", //5 28

L"Ashton：誰！あなた達はこの橋を\n渡ってはだめだよ！", //1 29

L"Rowan：その人はゾンビのリーダーでしたか？",
L"Ashton：いいや、俺はゾンビが大嫌いだよ！\n俺はゾンビのリーダーが出るのがほしくないからだ。\nだから、私はこの橋を壊した。",
L"Aeryk：はしを渡った後であなたと一緒に\nゾンビのリーダーが殺せませんか。",
L"Ashton：いいよ！", //4 33

L"Cal：あれはゾンビのリーダーですか。\n先生っぽいですね。",
L"Ashton：うん、そうだ、\nあれは怖くて危ないゾンビのリーダー",
L"Rowan：ゾンビのリーダーを殺すと、\n全部のゾンビが死にます。", //3 36

L"Aubrey：やった！私たちは勝った。",
L"Rowan：死にそうだった！",
L"Cal：食べられそうだった！",
L"ゾンビのリーダーを殺した時から、\n全部のゾンビは死にました。\nそして、このせかいは円満になりました。" //4 40
};
int Npc::voiceLinesLength[13] = {0, 5, 7, 8, 17, 20, 21, 23, 28, 29, 33, 36, 40};




Npc::Npc()
{

	setSize(sf::Vector2f(50, 50));
	setPosition(100,100);
	

	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);
}


Npc::Npc(CHARACTERS player)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);

	switch (player)
	{
	case AERYK:
		img.loadFromFile("./Sprites/characters/AE_L.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(225, 3200);
		break;
	case ASHTON:
	case AUBREY:
		img.loadFromFile("./Sprites/characters/AU_R.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(300, 3200);
		break;
	case PHOENIX:
	case ROWAN:
		img.loadFromFile("./Sprites/characters/AE_L.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(-10000, -10000);
		break;
	case STEVE:
	case BRIT:
	case KIMORA:
	case ALEX:
	case LEAH:
	case NATHAN:
	case BLANK:
		setSize(sf::Vector2f(600, 600));
		setPosition(0, 3100);
		break;
	case BOOK:
		img.loadFromFile("./Sprites/book.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setSize(sf::Vector2f(0, 0));
		setPosition(-100, -100);
		break;

	}


	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

}


Npc::~Npc()
{
}


//manage interactions and incrementing current line
void Npc::continueTalking(sf::RenderWindow& window)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	inputDelay++;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction == true 
		&& inputDelay > 5 && position.y > 300)
	{
		if (voiceLinesLength[CurrentInteraction] == currentLine)
		{
			std::cout << currentLine;
			currentLine++;
			CurrentInteraction++;
			interaction = false;
			std::cout << "interacted" << CurrentInteraction;


		}
		else
		{
			std::cout << currentLine;
			currentLine++;
			inputDelay = 0;
		}
	}
}


//display text
void Npc::talk(sf::RenderWindow &window, int x, int y)
{
	//do magic
	sf::RectangleShape outline, background;

	outline.setSize(sf::Vector2f(600, 300));
	outline.setPosition(0 + ((x - 1) * 600), 300 + ((y - 1) * 600));

	background.setSize(sf::Vector2f(580, 280));
	background.setPosition(10 + ((x - 1) * 600), 310 + ((y - 1) * 600));
	background.setFillColor(sf::Color::Black);

	text.setPosition(20 + ((x - 1) * 600), 320 + ((y - 1) * 600));

	window.draw(outline);
	window.draw(background);

	text.setString(voiceLines[currentLine]);

	window.draw(text);
}


void Npc::print(sf::RenderWindow& window)
{
	sprite.setPosition(getPosition().x, getPosition().y);
	window.draw(sprite);
}
