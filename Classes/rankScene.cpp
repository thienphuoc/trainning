#include "rankScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "rapidjson/document.h"

USING_NS_CC;
using namespace network;

Scene* RankScene::createScene()
{
    return RankScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RankScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto rankScene = CSLoader::getInstance()->createNode("csb/Rank.csb");
    this->addChild(rankScene);
    auto buttonReturn = rankScene->getChildByName<ui::Button*>("return_main");
    buttonReturn->setPressedActionEnabled(true);
    buttonReturn->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(RankScene::GoToMainMenu), 0);
        });
    loadData();
    

    



    return true;
}

void RankScene::GoToMainMenu(float dt) {
    auto mainMenu = MainMenuScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(0.5, mainMenu));
}

void RankScene::loadData() {
    HttpRequest* request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl("https://onetconnectjunior.firebaseio.com/leaderboard.json");
    request->setResponseCallback([=](HttpClient* sender, HttpResponse* response) {
        rapidjson::Document doc;
        if (200 == response->getResponseCode()) // connect success
        {
            std::vector<char>* buffer = response->getResponseData();

            std::string data = std::string(buffer->begin(), buffer->end());

            if (data.empty()) {
                return;
            }

            doc.Parse<rapidjson::ParseFlag::kParseStopWhenDoneFlag>((char*)data.c_str());
            if (doc.IsArray() && !doc.IsNull())
            {
                auto dataValue = doc.GetArray();

                for (int i = 0; i < dataValue.Size(); i++)
                {
                    if (dataValue[i].IsObject() && !dataValue[i].IsNull())
                    {
                        auto value = dataValue[i].GetObjectW();

                        if (value["name"].IsString() && !value["name"].IsNull() && value["score"].IsInt() && !value["score"].IsNull())
                        {
                            auto name = value["name"].GetString();
                            int score = value["score"].GetInt();
                            LeaderBoardInfo* player = new LeaderBoardInfo(name, score);
                            leader.push_back(player);
                        }
                    }
                }

            }


        }
        else // connect failed
        {
        }
        showData();
        });
    request->setTag("Get test");
    HttpClient::getInstance()->send(request);
    request->release();
}

void RankScene::showData()
{
    std::sort(leader.begin(), leader.end(), [](LeaderBoardInfo* first, LeaderBoardInfo* last) {
            return first->m_score > last->m_score;
        });
    for (auto i : leader)
    {
        //auto hightRank = this->getChildByName<ui::ImageView*>("item_bg");
        auto hightRank = utils::findChild<ui::ImageView*>(this, "item_bg");
        auto hr= hightRank->clone();
        
        auto namePlayer = hr->getChildByName<ui::Text*>("Name");
        auto scorre = hr->getChildByName<ui::Text*>("Score");
        namePlayer->setString(i->m_name);
        scorre->setString(std::to_string(i->m_score));
        auto listView= utils::findChild<ui::ListView*>(this, "ListView_1");
        listView->pushBackCustomItem(hr);
        if (std::find(leader.begin(), leader.end(), i) == (leader.begin() + 3)) {
            break;
        }
    }
    auto hightRank = utils::findChild<ui::ImageView*>(this, "item_bg");
    hightRank->removeFromParent();
}

