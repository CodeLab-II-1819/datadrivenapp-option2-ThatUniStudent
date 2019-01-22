/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:	MIT
*/


#include "ofApp.h"
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
    client.search("Brexit"); // Use this to search for certain queries
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
	btn1.set(20, 100, 200, 100);
	btn2.set(20, 200, 50, 50);
	btn3.set(20, 300, 50, 50);
	btn4.set(20, 400, 50, 50);
	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);

	int year = TM.tm_year + 1900;
	ss << year << std::endl;
}

/*
 Draw function is used to draw to GUI.
 Current setup simply draws tweet count info to a small GUI
 Tweets are displayed in console
*/
void ofApp::draw()
{
	//sets background to black
	ofBackground(192, 222, 237);
	ofSetColor(0, 200, 20);
	ofDrawRectangle(btn1);
	ofSetColor(20, 20, 210);
	ofDrawRectangle(btn2);
	ofSetColor(70, 120, 90);
	ofDrawRectangle(btn3);
	ofSetColor(30, 100, 20);
	ofDrawRectangle(btn4);
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
		CheckRepeat();
		//ofDrawBitmapString(ss.str(), 400, 50);
	//}

    /*
     Draw string stream info to the GUI window at x: 14 / y: 14
     Bitmap string is default text with limited customisation optimisations
     Load in fonts to enhance design
    */
    ofDrawBitmapString(ss.str(), 400, 50);
	//ss.str("");
}

void ofApp::GrabTweet() {
	ss << UserString << std::endl;
	ss << TweetString << std::endl;
	ss << std::endl;
	OldUser = UserString;
}
void ofApp::CheckRepeat() {
	if (OldUser.compare(UserString) != 0)
	{
		GrabTweet();
		std::cout << "Tweet out" << std::endl;
	}
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
	if (btn1.inside(x, y)) {
		std::cout << "Change to Brexit" << std::endl;
		client.search("Brexit");
		ss.str("");
	}
	if (btn2.inside(x, y)) {
		std::cout << "Change to Trump" << std::endl;
		client.search("Trump");
		ss.str("");
	}
	if (btn3.inside(x, y)) {
		std::cout << "Change to location" << std::endl;
		ofxTwitter::SearchQuery query("Bath Spa University");
		query.setGeoCode(51.3758, -2.3599, 10, ofxTwitter::SearchQuery::UNITS_MILES);
		query.setLanguage("en");
		client.search(query);
		//client.search("51.377177, -2.436948, 3mi");
		std::cout << "Bath Spa University Within 10 miles" << std::endl;
		ss.str("");
	}
	if (btn4.inside(x, y)) {
		std::cout << "Change to location" << std::endl;
		client.search("51.436600,-2.481097,1mi");
		ss.str("");
	}
}//https://developer.twitter.com/en/docs/tweets/filter-realtime/guides/basic-stream-parameters.html


