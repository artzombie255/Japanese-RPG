#include "Npc.h"
#include <iostream>

int Npc::CurrentInteraction = 0;
int Npc::currentLine = 0;
int Npc::inputDelay = 0;
sf::String Npc::voiceLines[43] = { L"オーブリー：助けてください！", //1 0

L"オーブリー：ゾンビたちは私たちを\n驚（おどろ）かしました。",
L"エリック：ゾンビが\n多過（おおす）ぎます。",
L"オーブリー：こちらはだめです。",
L"エリック：私たちを助けてくれるなら、\n私は転石（てんせき）が押（お）せます。",
L"エリック：行きましょう！", //5 5

L"オーブリー：私たちは\nはしを渡りたいなら、\nはしを直さなければなりません。",
L"エリック：うん、そうね、\n誰が橋を直せるでしょう。", //2 7

L"ローワン：誰ですか？！\nゾンビは帰ってくれませんか。\n私はおいしくない。", //1 8

L"ローワン：あ、人間か。どうやって、\n生（い）き残（のこ）りましたか。",
L"オーブリー：フェニックスは\n助けてくれました。",
L"エリック：うん、どうやって、\nあなたは生き残りましたか。",
L"ローワン：うちに入って、待ちました。",
L"オーブリー：そうですか。",
L"ローワン：ところで、\n私のマジックブックを\n無（な）くしました。\nこの町の南にあるでしょう。",
L"ローワン：ゾンビがいるから、あの町から\n逃（に）げなければなりませんでした。",
L"ローワン：私のマジックブックを\n持っていると、ゾンビと\n戦（たたか）えます。",
L"エリック：そうですか、私たちは\nあの町を調べます。", //9 17

L"オーブリー：あ、マジックブックを\n見つけました。",
L"エリック：ローワンと一緒に\nあのゾンビたちを殺せるかもしれません。",
L"オーブリー：うん、そうですね", //3 20

L"ローワン：ありがとうございます！\n今からゾンビと戦えます。",//1 21

L"エリック：あぁ、あの人はやばいです。",
L"オーブリー：うん、\n私たちは助けたほうがいいです。", //2 23

L"スティーブ：どうも有難うございます！\n助けてくれなかったら、死んだでしょう。\n私は何で礼をできますか。",
L"ローワン：橋を直せますか？",
L"スティーブ：うん、橋を直せます。\nでも、どうして、橋を渡りたいですか。",
L"オーブリー：最初にゾンビは\nあそこから来たと思うから。",
L"スティーブ：そうですか。それから、\n私は助けてゾンビのリーダーを殺せます。", //5 28

L"アシトン：誰！あなた達はこの橋を\n渡ってはだめだよ！", //1 29

L"ローワン：その人は\nゾンビのリーダーでしたか？",
L"アシトン：いいや、\n俺はゾンビが大嫌いだよ！\n俺はゾンビのリーダーが\n出るのがほしくないからだ。\nだから、私はこの橋を壊（こわ）した。",
L"エリック：はしを渡った後で\nあなたと一緒に\nゾンビのリーダーが殺せませんか。",
L"アシトン：いいよ！", //4 33

L"スティーブ：あれは\nゾンビのリーダーですか。\n先生っぽいですね。",
L"アシトン：うん、そうだ、\nあれは怖くて危（あぶ）ないゾンビのリーダー",
L"ローワン：ゾンビのリーダーを殺すと、\n全部のゾンビが死にます。", //3 36

L"先生：...",

L"オーブリー：やった！私たちは勝った。",
L"ローワン：死にそうだった！",
L"スティーブ：食べられそうだった！",
L"ゾンビのリーダーを殺した時から、\n全部のゾンビは死にました。そして、\nこのせかいは円満（えんまん）\nになりました。", //4 40
L""
};
int Npc::voiceLinesLength[15] = {0, 5, 7, 8, 17, 20, 21, 23, 28, 29, 33, 36, 37, 41, 42};

sf::String Npc::individualVoiceLines[3] = { L"Leah：いらっしゃいませ、\nおいしいたこやきを食べませんか！\n５０００円だけですよ。",
L"Leah：私はゾンビが大嫌いです。\nゾンビたちはたこやきを食べないからです。\nブレインだけ食べたいです。",
L"Leah：ゾンビが来る前に\nおいしいたこやきを売りました。\n今、せかいで一番おいしいたこやきを\n売っています。"
};


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
		img.loadFromFile("./Sprites/characters/AS_R.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(-1000, -1000);
		break;
	case AUBREY:
		img.loadFromFile("./Sprites/characters/AU_R.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(300, 3200);
		break;
	case PHOENIX:
	case ROWAN:
		img.loadFromFile("./Sprites/characters/R_L.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(-10000, -10000);
		break;
	case STEVE:
		img.loadFromFile("./Sprites/characters/S_F.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		setPosition(-10000, -10000);
		break;
	case BRIT:
	case KIMORA:
	case ALEX:
	case LEAH:
		setPosition(2800, 2050);
		img.loadFromFile("./Sprites/characters/L_F.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		leahLine = 0;
		break;
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
		//setSize(sf::Vector2f(0, 0));
		setPosition(-1000, -1000);
		break;
	case SENSEI:
		setSize(sf::Vector2f(100, 100));
		img.loadFromFile("./Sprites/zombies/sensei.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		//setSize(sf::Vector2f(0, 0));
		setPosition(-1000, 3200);
		break;
	}


	font.loadFromFile("NotoSansJP-VariableFont_wght.ttf");
	text.setFont(font);

}


Npc::~Npc()
{
}


//manage interactions and incrementing current line
void Npc::continueTalking(sf::RenderWindow& window, int temp)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);


	inputDelay++;

	if (temp != 8)
	{
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
	else
	{
		setPosition(2800, 2050);
		img.loadFromFile("./Sprites/characters/L_F.png");
		sprite.setTexture(img);
		sprite.setScale(3.125, 3.125);
		sprite.setPosition(getPosition().x, getPosition().y);
		inputDelay++;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && interaction == true
			&& inputDelay > 5 && position.y > 300)
		{
			interaction = false;
			if (leahLine >= 2)
				leahLine = 0;
			else
				leahLine++;
			inputDelay = 0;
		}
	}
}


//display text
void Npc::talk(sf::RenderWindow &window, int x, int y, int temp)
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

	if (temp != 8)
		text.setString(voiceLines[currentLine]);
	else
		text.setString(individualVoiceLines[leahLine]);

	window.draw(text);
}


void Npc::print(sf::RenderWindow& window)
{
	sprite.setScale(3.125, 3.125);
	sprite.setPosition(getPosition().x, getPosition().y);
	window.draw(sprite);
}
