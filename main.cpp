#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Player
{
  private:
    string Cards[2] = {};
    int Score = 0;

  public:
    Player()
    {
    }

    Player SetCard(string card, int index)
    {
        if (index >= 0 && index < 2)
        {
            this->Cards[index] = card;
        }
        return *this;
    }

    void SetScore(int score)
    {
        Score += score;
    }

    int GetScore()
    {
        return this->Score;
    }

    string GetCards()
    {
        return this->Cards[0] + ", " + this->Cards[1];
    }
};

// 카드 받는 함수
void Func_Get_Card(Player *player)
{
    for (int i = 0; i < 2; i++)
    {

        int randomNumber = (rand() % 12) + 1;
        string card;

        // 접수 합산
        // Sum += randomNumber;

        switch (randomNumber)
        {
        case 1:
            card = 'A';
            break;
        case 11:
            card = 'J';
            break;
        case 12:
            card = 'Q';
            break;
        case 13:
            card = 'K';
            break;
        default:
            card = to_string(randomNumber);
            break;
        }
        player->SetScore(randomNumber);
        player->SetCard(card, i);
    }
}

// 블랙잭 승자 계산 함수
string Func_Calc_BlackJack_Winner(Player *player1, Player *player2)
{
    int firstPlayerScore = player1->GetScore();
    int secondPlayerScore = player2->GetScore();

    // 둘다 21 안쪽인 경우
    if (firstPlayerScore <= 21 && secondPlayerScore <= 21)
    {

        if (firstPlayerScore == secondPlayerScore)
        {
            return "Draw By 21 = 21";
        }
        else if (firstPlayerScore > secondPlayerScore)
        {
            return to_string(firstPlayerScore) + " > " + to_string(secondPlayerScore) + " = Winner is Player1";
        }
        else
        {
            return to_string(firstPlayerScore) + " < " + to_string(secondPlayerScore) + " = Winner is Player2";
        }
    }
    // 둘다 21 넘는 경우
    else if (firstPlayerScore > 21 && secondPlayerScore > 21)
    {
        return "Both Player Lose By Bigger Than 21";
    }
    // 한쪽만 21 넘는 경우
    else if (firstPlayerScore > 21 || secondPlayerScore > 21)
    {
        // 플레이어 1의 스코어가 21이 넘은 경우
        if (firstPlayerScore > 21)
        {
            return "Player 1 Lose, By Bigger Than 21";
        }
        // 플레이어 2의 스코어가 21이 넘은 경우
        else
        {
            return "Plyaer 2 Lose, By Bigger Than 21";
        }
    }
}

int main()
{
    srand(time(NULL));

    // 컴퓨터 플레이어
    Player *computer = new Player();
    // 유저 플레이어
    Player *user = new Player();

    // 컴퓨터 카드 발급
    Func_Get_Card(computer);
    // 유저 카드 발급
    Func_Get_Card(user);

    // 컴퓨터 카드, 스코어 출력
    cout << computer->GetCards() << endl;
    cout << computer->GetScore() << endl;

    // 유저 카드, 스코어 출력
    cout << user->GetCards() << endl;
    cout << user->GetScore() << endl;

    // 승자 출력
    cout << Func_Calc_BlackJack_Winner(computer, user);

    // 해제
    delete computer;
    delete user;

    return 0;
}