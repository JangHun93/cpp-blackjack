#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Card
{
  private:
    int RemainCardCount = 52;
    string Cards[52] = {
        0,
    };

  public:
    Card()
    {
        for (int i = 1; i <= 52; i++)
        {
            Cards[i] = i;
        }
    }

    string ReleaseCard()
    {

        string PopCard = Cards[this->RemainCardCount];

        SetReaminCardCount(this->RemainCardCount - 1);

        return PopCard;
    }

    void SetReaminCardCount(int setNumber)
    {
        this->RemainCardCount += setNumber;
    }
};

// 플레이어 클래스
class Player
{
  private:
    // 보유 카드
    string Cards[2] = {};
    // 점수
    int Score = 0;
    // 플레이어 명
    string Nickname = "";

  public:
    // Default 생성자
    Player()
    {
    }
    // 닉네임 Set 생성자
    Player(string _nickName) : Nickname(_nickName)
    {
    }

    // 플레이어 카드 Settter
    Player SetCard(string card, int index)
    {
        if (index >= 0 && index < 2)
        {
            this->Cards[index] = card;
        }
        return *this;
    }

    void SetNickName(string nickName)
    {
        this->Nickname;
    }

    // 플레이어 점수 Setter
    void SetScore(int score)
    {
        this->Score += score;
    }

    // 플레이어 점수 Getter
    int GetScore()
    {
        return this->Score;
    }

    // 플레이어 카드 Getter
    string GetCards()
    {
        return this->Cards[0] + ", " + this->Cards[1];
    }

    // 플레이어 닉네임 Getter
    string GetNickName()
    {
        return this->Nickname;
    }
};

// 0 ~ 52
// ( 1 ~ 13 ) * 4 - 다이아,하트,클로버,

// 카드 받는 함수
void Func_Get_Card(Player *player, Card *card)
{
    // 2장 발급
    for (int i = 0; i < 2; i++)
    {
        // 0 ~ 52 중 하나 선택
        int randomNumber = (rand() % 52);
        int cardType = randomNumber % 4;
        string card;

        // 접수 합산
        // Sum += randomNumber;

        switch (randomNumber / 4)
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

// PlyaerTotal = ((PlayerCard[0] % 12 + 1)) +
// ComputerTotal = ((ComputerCard[0] % 12 ) + 1) +

// 블랙잭 승자 계산 함수
string Func_Calc_BlackJack_Winner(Player *player1, Player *player2)
{
    int firstPlayerScore = player1->GetScore();
    int secondPlayerScore = player2->GetScore();

    // 둘다 21 안쪽인 경우
    if (firstPlayerScore <= 21 && secondPlayerScore <= 21)
    {
        // 동점인 경우
        if (firstPlayerScore == secondPlayerScore)
        {
            return "Draw By 21 = 21";
        }
        // 플레이어1이 점수가 높은 경우
        else if (firstPlayerScore > secondPlayerScore)
        {
            return to_string(firstPlayerScore) + " > " + to_string(secondPlayerScore) + " = Winner is " +
                   player1->GetNickName();
        }
        // 플레이어2가 점수가 높은 경우
        else
        {
            return to_string(firstPlayerScore) + " < " + to_string(secondPlayerScore) + " = Winner is " +
                   player2->GetNickName();
        }
    }
    // 둘다 21 넘는 경우
    else if (firstPlayerScore > 21 && secondPlayerScore > 21)
    {
        return "Both LOSE! (Bigger Than 21)";
    }
    // 한쪽만 21 넘는 경우
    else if (firstPlayerScore > 21 || secondPlayerScore > 21)
    {
        // 플레이어 1의 스코어가 21이 넘은 경우
        if (firstPlayerScore > 21)
        {
            return player1->GetNickName() + " LOSE! (Bigger Than 21)";
        }
        // 플레이어 2의 스코어가 21이 넘은 경우
        else
        {
            return player2->GetNickName() + " LOSE! (Bigger Than 21)";
        }
    }
}

int main()
{
    // 난수 랜덤화
    srand(time(nullptr));

    // 컴퓨터 플레이어
    Player *computer = new Player("Computer");
    // 유저 플레이어
    // Player *user = new Player();
    Player *user = new Player("JangHun");

    // string UserNickName = "";
    // cout << "Enter NickName: ";
    // cin >> UserNickName;
    // getline(cin, UserNickName);
    // user->SetNickName(UserNickName);

    // 카드 생성
    Card *card = new Card();

    // 컴퓨터 카드 발급
    Func_Get_Card(computer, card);
    // 유저 카드 발급
    Func_Get_Card(user, card);

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