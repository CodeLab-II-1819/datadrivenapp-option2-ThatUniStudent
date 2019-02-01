/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:	MIT
*/


#include "ofApp.h"
#include <string>
#include <sstream>
#include <ctime>
//initial app setup
void ofApp::setup()
{
    //lower app frameRate
    ofSetFrameRate(60);

    // Easily register for all search events.
    client.registerSearchEvents(this);

    /* Ensure you have created and app and updated the credentials file
     in the bin/data folder. You can create app at:
     https://apps.twitter.com */
    //Load in the credentials for access to twitter
    client.setCredentialsFromFile("credentials.json");

    /* Sets the polling interval for 6 seconds. This means new tweets
    are retrived every 6 seconds*/
    client.setPollingInterval(1000);

    // This starts a simple search for an emoticon.
    //client.search("Brexit"); // Use this to search for certain queries
	//client.stop();
    // Tweets are retured in the callbacks onStatus(..), onError(...), etc.

    /*
     To design more complex searches, see the the API documentation here:
     https://dev.twitter.com/rest/public/search
     and:
     https://developer.twitter.com/en/docs/tweets/rules-and-filtering/overview/standard-operators
     You can then use the search object ofxTwitter::SearchQuery like this:
     
        ofxTwitter::SearchQuery query(":)");
        query.setLanguage("en");
        client.search(query);

     This would return only tweets in English
    
     To see how else you can refine the queries you should explore
     the .h files included in:
     openFrameworks/addons/ofxTwitter/libs/ofxTwitter/include/ofx/Twitter
     In particular search.h
    */
	liveOff.set(500, 20, 400, 50);
	btn1.set(20, 175, 100, 50);
	btn2.set(20, 250, 100, 50);
	btn3.set(20, 325, 100, 50);
	btn4.set(20, 400, 100, 50);
	btn5.set(20, 475, 100, 50);
	btn6.set(20, 550, 100, 50);
	btn10.set(20, 625, 100, 50);

	CarbonBlock.load("CARBONBL.TTF", 14, true, true);
	CarbonBlock.setLineHeight(18.0f);
	CarbonBlock.setLetterSpacing(1.037);
	Candara.load("Candara.ttf", 14, true, true);
	Candara.setLineHeight(18.0f);
	Candara.setLetterSpacing(1.037);

	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);

	year = TM.tm_year + 1900;
	month = TM.tm_mon;
	day = TM.tm_mday;
	//TodayDate = year + "-" + month;// "-" + day;
	//string Date = TodayDate + "-" + day;
	//std::cout << TodayDate << std::endl;
}

/*
 Draw function is used to draw to GUI.
 Current setup simply draws tweet count info to a small GUI
 Tweets are displayed in console
*/
void ofApp::draw()
{
	//sets background to Twitter Background Colour
	ofBackground(192, 222, 237);
	ofSetColor(0, 132, 180);
	ofDrawRectangle(liveOff);
	//liveOff.drawString("Roll");
	ofSetColor(0, 200, 20);
	ofDrawRectangle(btn1);
	ofSetColor(20, 20, 210);
	ofDrawRectangle(btn2);
	ofSetColor(70, 120, 90);
	ofDrawRectangle(btn3);
	ofSetColor(30, 100, 20);
	ofDrawRectangle(btn4);
	ofSetColor(60, 200, 40);
	ofDrawRectangle(btn5);
	ofSetColor(100, 200, 40);
	ofDrawRectangle(btn6);
	ofSetColor(120, 200, 40);
	ofDrawRectangle(btn7);
	ofSetColor(140, 200, 40);
	ofDrawRectangle(btn8);
	ofSetColor(170, 200, 40);
	ofDrawRectangle(btn9);
	ofSetColor(80, 200, 40);
	ofDrawRectangle(btn10);
	ofSetColor(50, 50, 50);
	ofSetLineWidth(4.0f); 
	ofDrawLine(5, 100, ofGetWidth() - 5, 100);
	ofDrawLine(200, 100, 200, ofGetHeight() - 5);
	//counts number of tweets
	int total = count + countMissed;

	//string stream used to display number of tweets recived
	//std::stringstream ss;
	//ss << "  Received: " << count << std::endl;
	//ss << "    Missed: " << countMissed << std::endl;
   // ss << "     Total: " << total << std::endl;
	//for (int x = 0; x < 5; x++) {
		//ss << UserString << std::endl;
		//ss << TweetString << std::endl;
		//ss << year << std::endl;
		//ss << std::endl;
	//}
	//for (int x = 0; x > 15; x++)

	//{
	if ((ssCount % 20) == 0)
	{
		ss.str("");
	}
		CheckRepeat();
		//ofDrawBitmapString(ss.str(), 400, 50);
	//}

    /*
     Draw string stream info to the GUI window at x: 14 / y: 14
     Bitmap string is default text with limited customisation optimisations
     Load in fonts to enhance design
    */
    //ofDrawBitmapString(ss.str(), 400, 50);
		ofSetColor(124, 124, 124);
		Candara.drawString(ss.str(), 225, 135);
	//ss.str("");
		/*if (IsUserName == true)
		{
			std::cout << "UserNameFont" << std::endl;
			ofSetColor(8, 160, 233);
			CarbonBlock.drawString(ssU.str(), 400, 50);
			//ofDrawBitmapString(ss.str(), 400, 50);
		}
		if (IsUserName == false)
		{
			ofSetColor(232, 245, 253);
			Candara.drawString(ssT.str(), 600, 50);
		}*/
}

void ofApp::GrabTweet() {
	//UserString.ofSetColor(8, 160, 233);
	ss << UserString << std::endl;
	//IsUserName = true;
	ssDraw();
	//ofSetColor(232, 245, 253);
	ss << TweetString << std::endl;
	ss << std::endl;
	//IsUserName = false;
	ssDraw();
	OldUser = UserString;
}
void ofApp::CheckRepeat() {
	if (OldUser.compare(UserString) != 0)
	{
		GrabTweet();
		std::cout << "Tweet out" << std::endl;
	}
}
void ofApp::ssDraw()
{
	/*if (IsUserName == true)
	{
		std::cout << "UserNameFont" << std::endl;
		CarbonBlock.drawString(ss.str(), 400, 50);
		ofDrawBitmapString(ss.str(), 400, 50);
	}
	if (IsUserName == false)
	{
		Candara.drawString(ss.str(), 400, 50);
	}*/
	//ofDrawBitmapString(ss.str(), 400, 50);
	ssCount++;
}
//This function is called everytime the a new tweet is recieved
void ofApp::onStatus(const ofxTwitter::Status& status)
{
    //increase tweet count
    count++;
	//Have moving panels that go down and clear when off the screen
    //output the tweet author and text
    UserString = "User: " + status.user()->name();
	//string OldUser = UserString;
	//ss << "User: " + status.user()->name() << endl;
	TweetString = "Tweet: " + status.text();
	//ss << "Tweet: " + status.text() << endl;
	std::cout << "User: " + status.user()->name() << endl;
	std::cout << "Tweet: " + status.text() << endl;
    std::cout << "\n -----------------------------\n" << endl;
    /*
     To see what other information you can display you should explore
     the .h files included in:
     openFrameworks/addons/ofxTwitter/libs/ofxTwitter/include/ofx/Twitter
     In particular status.h
    */
	//draw();
}

//returns an error message if error encountered recieving tweets
void ofApp::onError(const ofxTwitter::Error& error)
{
    std::cout << "Error: " << error.code() << " " << error.message();
}

//returns an exception message if exception encountered recieving tweets
void ofApp::onException(const std::exception& notice)
{
    std::cout << "Exception: " << notice.what();
}

void ofApp::onMessage(const ofJson& json)
{
	// This is the raw message json and is ignored here.
}
void ofApp::mousePressed(int x, int y, int button) { //When a button is pressed it changes the subject
	if (liveOff.inside(x, y))
	{
		std::cout << "Live rolling off" << std::endl;
		client.stop();
	}
	if (btn1.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Change to Brexit" << std::endl;
		ofxTwitter::SearchQuery query("Brexit");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
		//ss.str("");
	}
	if (btn2.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Change to Trump" << std::endl;
		ofxTwitter::SearchQuery query("Trump");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
		//ss.str("");
	}
	if (btn3.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Change to location Oxford" << std::endl;
		ofxTwitter::SearchQuery query("");
		query.setGeoCode(51.7520, 1.2577, 10, ofxTwitter::SearchQuery::UNITS_MILES);
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn4.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Change to Tweets from SpaceX" << std::endl;
		ofxTwitter::SearchQuery query("from:SpaceX");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
		//ss.str("");
	}
	if (btn5.inside(x, y)) {
		//ssCount = 0;
		std::cout << "#happy tweets" << std::endl;
		ofxTwitter::SearchQuery query("#happy");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn6.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Popular tweets from today" << std::endl;
		ofxTwitter::SearchQuery query("");
		query.setUntil(year, month, day);
		query.setResultType(ofxTwitter::SearchQuery::ResultType::POPULAR);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn7.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Puppy's" << std::endl;
		ofxTwitter::SearchQuery query("dog filter:media");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::POPULAR);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn10.inside(x, y)) {
		//ssCount = 0;
		std::cout << "Change to location" << std::endl;
		ofxTwitter::SearchQuery query("Bath Spa University");
		query.setGeoCode(51.3758, -2.3599, 10, ofxTwitter::SearchQuery::UNITS_MILES);
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setLanguage("en");
		client.search(query);
		//client.search("51.377177, -2.436948, 3mi");
		std::cout << "Bath Spa University Within 10 miles" << std::endl;
		//ss.str("");
	}
}//https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/basic-stream-parameters.html


