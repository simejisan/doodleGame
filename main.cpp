

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <list>
#include <string>
#include <cstring>
#include <Windows.h>
#include "Function.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace Engine;

struct point
{ int x,y;};

const string PathImage = "Resource/Images/";
const string File = "Resource/File/HighScore.txt";
const string Fonts = "Resource/Fonts/al-seana.ttf";
const string Musics = "Resource/Musics/";
//
unsigned long long ReadFile()
{
	ifstream Read;
	Read.open(File);
	unsigned int score;
	Read >> score;
	Read.close();
	return score;
}

void WriteFile(unsigned long long score)
{
	ofstream Write;
	Write.open(File);
	Write.clear();
	Write << score;
	Write.close();
}
//
void PlayGame(RenderWindow &window){
	if (Keyboard::isKeyPressed(Keyboard::Escape)) return;
    srand(time(0));
    Texture background, plat, doodle, dead;
	background.loadFromFile(PathImage + "background.png");

	plat.loadFromFile(PathImage + "plat.png");
	doodle.loadFromFile(PathImage + "doodle2.png");
	dead.loadFromFile(PathImage +"game_over.png");
	Sprite Background(background), Plat(plat), Doodle(doodle), gameOver(dead);
	Doodle.setPosition(0, 524);


//	Text Score;
//	Score.setFont(font);
//	Score.setFillColor(Color::Red);
//	Score.setPosition(5,10);
//	Score += 1.f/60.f;
//	Score.setString("Score: " + to_string)

	SoundBuffer backgroundSound, jumpStep, die;
	backgroundSound.loadFromFile(Musics + "Wing.wav");
	jumpStep.loadFromFile(Musics + "Point.wav");
	die.loadFromFile(Musics + "Die.wav");
	Sound BackgroundSound(backgroundSound),
          Jump(jumpStep), Die(die);
    BackgroundSound.setBuffer(backgroundSound);

    Music musicBackgroud,dieMusic;
	if (!musicBackgroud.openFromFile(Musics + "battle.wav"))
        return;
    if (!dieMusic.openFromFile(Musics + "Die.wav"))
        return;
    musicBackgroud.play();
    musicBackgroud.setLoop(true);
    //score

    Text Score;

	float score = 0;
	Clock clock; // starts the clock
    Time elapsed = clock.getElapsedTime();
    cout << elapsed.asSeconds() << endl;

	Font font;
	font.loadFromFile(Fonts);
	Score.setFont(font);
	Score.setFillColor(Color::Blue);
	Score.setStyle(Text::Bold);
	Score.setPosition(8,18);
    Score.setCharacterSize(20);
    Score.setString(L"Score: " + Engine::int_to_wstring(int(score)));
    score += 1.f/60.f;



    point platform[20];

    for (int i=0;i<10;i++)
      {
       platform[i].x=rand()%400;
       platform[i].y=rand()%533;
      }

	int x=100,y=100,h=200;
    float dx=0,dy=0;

    while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

    if (Keyboard::isKeyPressed(Keyboard::Right)) x+=7;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=7;

    dy+=0.2;
    y+=dy;

    score += 1.f/60.f;

	if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      platform[i].y=platform[i].y-dy;
      if (platform[i].y>533) {platform[i].y=0; platform[i].x=rand()%400;}
    }

	for (int i=0;i<10;i++)
    if ((x+50>platform[i].x) && (x+20<platform[i].x+68)
    && (y+70>platform[i].y) && (y+70<platform[i].y+14) && (dy>0))  dy=-9;

//    Score.setString(to_string(score));

	Doodle.setPosition(x,y);

    window.draw(Background);

    for (int i=0;i<10;i++)
    {
    Plat.setPosition(platform[i].x,platform[i].y);
    window.draw(Plat);
    }
    window.draw(Doodle);

    cout << elapsed.asSeconds() << endl;


   	window.draw(Score);

    window.display();


    if (y>500){
    musicBackgroud.stop();
    dieMusic.play();
    window.clear();
    window.draw(gameOver);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        return;
        }}}
//		window.clear();
//		window.draw(background);
//		window.draw(plat);
//		window.draw(doodle);
//		window.draw(Score);
		//Target.ChangeXY();
		//Ball.ChangeXY();
		// KIỂM TRA VA CHẠM
//PlayGame(window);
void Menu(RenderWindow &window)
{
	Texture background;
	background.loadFromFile(PathImage + "backgroundMenu.png");
	Sprite Background(background);
	Texture play, x;
	play.loadFromFile(PathImage + "PlayButton.png");
	x.loadFromFile(PathImage + "exit.png");
	Music music;
	if (!music.openFromFile(Musics + "background.wav"))
        return;
    SoundBuffer openSound;
    if (!openSound.loadFromFile(Musics + "meow.wav"))
        cout<<"Can't load meow";
    Sound OpenSound;
    OpenSound.setBuffer(openSound);
    music.play();
    music.setLoop(true);
	Sprite Play(play), GetOut(x);
	Play.setOrigin(52, 29);
	GetOut.setOrigin(60, 20);
	Play.setPosition(130, 250);
	GetOut.setPosition(140, 340);
	GetOut.setColor(Color::White);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.clear();
//		    window.draw (gameOver);

		window.draw(Background);
		window.draw(Play);
		window.draw(GetOut);

		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return;

		if (Mouse::isButtonPressed(Mouse::Left)
        && Mouse::getPosition(window).x >= 140
        && Mouse::getPosition(window).x <= 242
        && Mouse::getPosition(window).y >= 220
        && Mouse::getPosition(window).y <= 279){
            music.stop();
            OpenSound.play();
            PlayGame(window);}


		if (Mouse::isButtonPressed(Mouse::Left)
        && Mouse::getPosition(window).x >= 130
        && Mouse::getPosition(window).x <= 250
        && Mouse::getPosition(window).y >= 330
        && Mouse::getPosition(window).y <= 370) return ;
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RenderWindow window(VideoMode(400, 533), "Doodle Jump!", Style::Titlebar);
    window.setFramerateLimit(60);
    Image Icon;
    Icon.loadFromFile(PathImage + "icon.ico");
    window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
	Menu(window);
	return 0;
}


