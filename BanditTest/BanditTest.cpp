#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include "../bandit/highscore.h"
#include "../bandit/hiscore_entry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BanditTest
{
	TEST_CLASS(BanditTest)
	{
	public:
		
		TEST_METHOD(Test01ReadHiscore)
		{
			std::string hiscore{ "1000 2025.09.17 20:38 Andreas" };
			Hiscore_entry entry{ Highscore::read_hiscore(hiscore) };
			Assert::AreEqual(1000, entry.score);
			std::string date_expected{ "2025.09.17" };
			std::string date_actual{ entry.date };
			Assert::AreEqual(date_expected.c_str(), date_actual.c_str());
			std::string time_expected{ "20:38" };
			std::string time_actual{ entry.time };
			Assert::AreEqual(time_expected.c_str(), time_actual.c_str());
			std::string player_expected{ "Andreas" };
			std::string player_actual{ entry.player };
			Assert::AreEqual(player_expected.c_str(), player_actual.c_str());
		}

		TEST_METHOD(Test02WriteHiscore)
		{
			Hiscore_entry hiscore{ 1000, "2025.09.18", "19:57", "Andreas" };
			std::string hiscore_str{ Highscore::write_hiscore(hiscore) };
			std::string hiscore_expected = "1000 2025.09.18 19:57 Andreas";
			Assert::AreEqual(hiscore_expected.c_str(), hiscore_str.c_str());
		}

		TEST_METHOD(Test03SortHiscores)
		{
			std::vector<Hiscore_entry> hiscores{
				{1000, "2025.09.18", "19:57", "Andreas"},
				{500, "2025.09.18", "19:56", "Andreas"},
				{2000, "2025.09.18", "19:58", "Andreas"},
				{2500, "2025.09.18", "19:55", "Andreas"},
				{1500, "2025.09.18", "19:59", "Andreas"}
			};
			auto hiscores_sorted{ Highscore::sort_hiscores(hiscores) };
			Assert::AreEqual(2500, hiscores_sorted[0].score);
			Assert::AreEqual(2000, hiscores_sorted[1].score);
			Assert::AreEqual(1500, hiscores_sorted[2].score);
			Assert::AreEqual(1000, hiscores_sorted[3].score);
			Assert::AreEqual(500, hiscores_sorted[4].score);
		}

		TEST_METHOD(Test04LoadHiscoresIntoStruct)
		{
			std::string filename = "test_hiscores.txt";
			std::ofstream ofs(filename);
			ofs
				<< "500 2025.09.17 20:38 Andreas\n"
				<< "1500 2025.09.17 22:38 Andreas\n"
				<< "1000 2025.09.17 21:38 Andreas\n";
			ofs.close();

			Highscore highscore{ "./test_hiscores.txt", "./temp.txt" };

			highscore.load_hiscores_into_struct();
			Assert::AreEqual(highscore.highscores_struct->at(0).score, 500);
			Assert::AreEqual(highscore.highscores_struct->at(1).score, 1500);
			Assert::AreEqual(highscore.highscores_struct->at(2).score, 1000);
			
			auto hiscores_sorted{
				Highscore::sort_hiscores(*highscore.highscores_struct)
			};
			Assert::AreEqual(hiscores_sorted[0].score, 1500);
			Assert::AreEqual(hiscores_sorted[1].score, 1000);
			Assert::AreEqual(hiscores_sorted[2].score, 500);

			highscore.highscores_in.close();
			highscore.highscores_out.close();

			std::remove("test_hiscores.txt");
			std::remove("temp.txt");
		}
	};
}
