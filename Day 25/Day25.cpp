#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

int main()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto keys = reader.ReadValues();

  int cardPublicKey = keys[0];
  int doorPublicKey = keys[1];
  int subjectNumber = 7;

  int cardLoopSize = 0, doorLoopSize = 0, cardSubject = 1, doorSubject = 1;

  while (cardSubject != cardPublicKey)
  {
    cardLoopSize++;
    cardSubject *= subjectNumber;
    cardSubject = cardSubject % 20201227;
  }

  while (doorSubject != doorPublicKey)
  {
    doorLoopSize++;
    doorSubject *= subjectNumber;
    doorSubject = doorSubject % 20201227;
  }

  long long cardEncryptionKey = 1;
  for (int i = 0; i < doorLoopSize; i++)
  {
    cardEncryptionKey *= cardSubject;
    cardEncryptionKey = cardEncryptionKey % 20201227;
  }

  long long doorEncryptionKey = 1;
  for (int i = 0; i < cardLoopSize; i++)
  {
    doorEncryptionKey *= doorSubject;
    doorEncryptionKey = doorEncryptionKey % 20201227;
  }

  assert(cardEncryptionKey == doorEncryptionKey);

  cout << cardEncryptionKey;

  return 0;
}
