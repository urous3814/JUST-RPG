# JUST RPG 🎮
### 기능 요소

1. **스토리 및 게임 틀:** 
   - 기존의 로그라이크 게임을 기반으로 합니다. 플레이어는 던전을 탐험하여 보스를 물리치는 것이 목표입니다.

2. **맵 생성:** 
   - 이진 공간 분할법을 사용하여 절차적으로 맵을 생성합니다. 
   - 맵 생성 과정에서 랜덤 시드나 사용자 입력을 받아 맵 샘플을 생성하고, 이후에 맵 배열에 각 방과 특수 오브젝트를 배치합니다.

3. **레벨 디자인:** 
   - 게임 생성시 입력하는 난이도 가중치에 따라 앞서 생성한 맵의 각 방의 타입을 지정하고 오브젝트들을 생성합니다. 
   - 몹, 미믹, 앨리트, 보스몹 등 생성된 오브젝트들은 별도의 z레이어 배열 상에서 배치되며 오브젝트의 수에 난이도가 곱연산됩니다. 
   - 각 몹의 스탯은 레벨 가중치에 따라 랜덤 생성됩니다. 
   - 아이템 드롭은 사전에 만든 루팅 테이블에서 랜덤으로 추출됩니다.

4. **전투 시스템:** 
   - 플레이어의 공격은 플레이어가 지닌 장비의 스킬을 사용합니다. 
   - 각 스킬은 시전 범위와 마나 소모 등을 가지며, 플레이어가 착용할 수 있는 장비는 최대 3개로 제한됩니다.

5. **몹의 움직임:** 
   - 플레이어 시야 범위 내의 몹은 각각 개별적인 연산을 통해 이동 및 행동합니다. 
   - 몹의 행동은 피격 연산 > 상태 연산 > 이동 연산 > 렌더링 순서로 진행됩니다. 
   - 이동은 플레이어에 가까워지는 방향으로 수행됩니다. 
   - 멀티스레드를 이용한 병렬연산을 수행하고 맵과 별도인 z레이어 위에서 이동을 수행합니다.

6. **플레이어의 움직임:** 
   - 플레이어는 방향키를 통해 이동이 가능하며 탑뷰 시점이동 방식으로 이동을 표현합니다. 
   - 플레이어는 신속의 가호를 부여받았다는 설정으로, 몹이 1-3턴에 한 번 이동하는 반면 1턴에 한 번 이동 혹은 공격을 수행합니다.

7. **화면 렌더링:** 
   - 화면은 모든 내부 연산이 끝난 후에 렌더링을 진행하며 시야범위에 따른 맵 포인터, z레이어 포인터를 증감 시키는 방식으로 시야범위를 저장하며 맵 레이어 상의 벽 -> z레이어상의 오브젝트 순으로 렌더링됩니다.

8. **사운드 및 설정:** 
   - 게임은 백그라운드로 BGM을 재생하며, 플레이어는 사운드 크기 등을 설정하여 조절할 수 있습니다. 
   - 게임의 전체적인 설정을 파일로 저장하고 불러올 수 있습니다.

### 아이템 설명:
- **골드:** 
  - 상점에서 아이템을 구매하거나 기타 아이템들과 거래할 때 사용됩니다.
- **경험치:** 
  - 플레이어의 레벨업을 위해 필요하며, 몬스터 처치나 보물상자를 통해 획득할 수 있습니다.
- **아이템:** 
  - 액티브 스킬 아이템, 패시브 스킬 아이템, 소모성 아이템 등 다양한 아이템을 플레이어는 획득할 수 있습니다.

## 사용 요소

- **프로젝트 구성 언어:**
  ![C 언어 Badge](https://img.shields.io/badge/language-C-blue)

- **개발 환경 및 도구:**
  ![Visual Studio Badge](https://img.shields.io/badge/IDE-Visual%20Studio-purple)
  ![VS Code Badge](https://img.shields.io/badge/IDE-VS%20Code-blueviolet)
  ![GitHub Copilot Badge](https://img.shields.io/badge/Tool-GitHub%20Copilot-informational)
