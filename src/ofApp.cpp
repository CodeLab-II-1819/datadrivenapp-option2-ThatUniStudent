/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:	MIT
*/


#include "ofApp.h"
#include <string>
#include <sstream>
//initial app setup
void ofApp::setup()
{
    //High frame rate to call on tweets faster
    ofSetFrameRate(60);

    // Easily register for all search events.
    client.registerSearchEvents(this);

    //Load in the credentials for access to twitter
    client.setCredentialsFromFile("credentials.json");

    // Calls on Twitter to receive new tweets. This means new tweets are retrieved every second
    client.setPollingInterval(1000);

	liveOff.set(500, 20, 400, 50);
	btn1.set(20, 175, 150, 50);
	btn2.set(20, 250, 150, 50);
	btn3.set(20, 325, 150, 50);
	btn4.set(20, 400, 150, 50);
	btn5.set(20, 475, 150, 50);
	btn6.set(20, 550, 150, 50);
	btn7.set(20, 625, 150, 50);
	btn8.set(20, 700, 150, 50);
	btn9.set(20, 775, 150, 50);
	btn10.set(20, 850, 150, 50);
	// These are the many buttons for the GUI
	logo.load("TwitterLogo.png"); // loads in the logo for the corner
	CarbonBlock.load("CARBONBL.TTF", 14, true, true); // The 2 fonts that are used, called by the TTF file and then the font
	CarbonBlock.setLineHeight(18.0f);
	CarbonBlock.setLetterSpacing(1.037); // this sets the format of the font
	Candara.load("Candara.ttf", 14, true, true);
	Candara.setLineHeight(18.0f);
	Candara.setLetterSpacing(1.037); 
}

/*
 Draw function is used to draw to GUI.
 Current setup simply draws tweet count info to a small GUI
 Tweets are displayed in console for debuging and watching what tweets are going through
*/
void ofApp::draw()
{
	ofBackground(192, 222, 237); //sets background to Twitter Background Colour
	ofSetColor(0, 132, 180);
	ofDrawRectangle(liveOff);
	ofSetColor(188, 22, 22);
	ofDrawRectangle(btn1);
	ofSetColor(188, 22, 22);
	ofDrawRectangle(btn2);
	ofSetColor(21, 150, 44);
	ofDrawRectangle(btn3);
	ofSetColor(13, 104, 137);
	ofDrawRectangle(btn4);
	ofSetColor(255, 255, 28);
	ofDrawRectangle(btn5);
	ofSetColor(160, 33, 160);
	ofDrawRectangle(btn6);
	ofSetColor(160, 33, 160);
	ofDrawRectangle(btn7);
	ofSetColor(209, 136, 35);
	ofDrawRectangle(btn8);
	ofSetColor(76, 99, 0);
	ofDrawRectangle(btn9);
	ofSetColor(23, 41, 145);
	ofDrawRectangle(btn10);
	ofSetColor(50, 50, 50);
	// Most of the buttons are set their colours here and drawn
	ofSetLineWidth(4.0f); 
	ofDrawLine(5, 100, ofGetWidth() - 5, 100);
	ofDrawLine(200, 100, 200, ofGetHeight() - 5);
	// 2 lines to seperate the header from the buttons and the tweets
	logo.draw(20, 20); // draws the logo on
	CarbonBlock.drawString("Choose a subject", 25, 145);
	CarbonBlock.drawString("Brexit", 45, 205);
	CarbonBlock.drawString("Trump", 45, 280);
	CarbonBlock.drawString("Oxford", 45, 355);
	CarbonBlock.drawString("SpaceX", 45, 430);
	CarbonBlock.drawString("#Happy", 45, 505);
	CarbonBlock.drawString("Popular", 45, 580);
	CarbonBlock.drawString("Random", 45, 655);
	CarbonBlock.drawString("Dogs", 45, 730);
	CarbonBlock.drawString("Sponsored", 45, 805);
	CarbonBlock.drawString("Bath Spa Uni", 45, 880);
	CarbonBlock.drawString("Stop Incoming Tweets", 600, 45);
	// draws all the text out for the GUI
	
	if ((ssCount % 20) == 0) // Every 20 lines (10 tweets with usernames) the screen clears allowing for 20 new lines
	{
		ss.str(""); // this clears the string stream
	}
		CheckRepeat(); // calls on the checkRepeat to prevent spam
		
		ofSetColor(124, 124, 124);
		Candara.drawString(ss.str(), 225, 135); // this line prints out the tweet with the font Candara
}

void ofApp::GrabTweet() { //GrabTweet prints the tweets and sends back the tweet for spam prevention
	ss << UserString << std::endl;
	ssDraw();
	ss << TweetString << std::endl;
	ss << std::endl;
	ssDraw();
	OldUser = UserString; // this is the temp variable for the checkRepeat function
}
void ofApp::CheckRepeat() { //This function is to check that after every cycle it doesnt output the same tweet and thus stopping the spam of tweets
	if (OldUser.compare(UserString) != 0) // compares the 2 strings
	{
		GrabTweet(); // if the tweet is different it then calls GrabTweet
		std::cout << "Tweet out" << std::endl;
	}
}
void ofApp::ssDraw()
{
	ssCount++; // counts everytimes a line is printed out for the clearing code
}
//This function is called everytime the a new tweet is recieved
void ofApp::onStatus(const ofxTwitter::Status& status)
{
    //output the tweet author and text
    UserString = "User: " + status.user()->name(); // puts the tweet and author into a stringstream
	TweetString = "Tweet: " + status.text();
	std::cout << "User: " + status.user()->name() << endl; // outputing to the console means I can see what tweets are coming through and being outputted
	std::cout << "Tweet: " + status.text() << endl;
    std::cout << "\n -----------------------------\n" << endl;
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
		client.stop();	// This stops the programme calling on the Twitter API
	}
	if (btn1.inside(x, y)) { // if the mouse click is in the x and y of the button then it will trigger the if statement
		std::cout << "Change to Brexit" << std::endl;
		ofxTwitter::SearchQuery query("Brexit"); // Changes the query to what is in the quotation mark
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED); // The result type filters the results into 3 different categories
		// MIXED, POPULAR and RECENT, MIXED is a mix of POPULAR and RECENT tweets
		query.setCount(1); //This reduces the number of tweets to return
		query.setLanguage("en"); // This sets the language of the tweets to return
		client.search(query); //This actually searches the query
	}
	if (btn2.inside(x, y)) {
		std::cout << "Change to Trump" << std::endl;
		ofxTwitter::SearchQuery query("Trump");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn3.inside(x, y)) {
		std::cout << "Change to location Oxford" << std::endl;
		ofxTwitter::SearchQuery query("");
		query.setGeoCode(51.7520, 1.2577, 10, ofxTwitter::SearchQuery::UNITS_MILES); //This GeoCode commands allows to search for tweets in a radius
		// the first number is the longitude, then the latitude, then the radius number followed by what the measurement is
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn4.inside(x, y)) {
		std::cout << "Change to Tweets from SpaceX" << std::endl;
		ofxTwitter::SearchQuery query("from:SpaceX"); // from: means from the user
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn5.inside(x, y)) {
		std::cout << "#happy tweets" << std::endl;
		ofxTwitter::SearchQuery query("#happy");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn6.inside(x, y)) {
		std::cout << "Popular tweets from the week" << std::endl;
		ofxTwitter::SearchQuery query("%20 since:2019-02-01"); // &20 means space and since is sent since date
		query.setResultType(ofxTwitter::SearchQuery::ResultType::POPULAR);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn7.inside(x, y)) {
		std::cout << "Random Tweets" << std::endl;
		ofxTwitter::SearchQuery query("%20");
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn8.inside(x, y)) {
		std::cout << "Puppy's" << std::endl;
		ofxTwitter::SearchQuery query("dog filter:media"); // filter:media means containing the query and an image or video
		query.setResultType(ofxTwitter::SearchQuery::ResultType::POPULAR);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn9.inside(x, y)) {
		std::cout << "Random sponsored tweets" << std::endl;
		ofxTwitter::SearchQuery query("sponsor -filter:retweets"); // -filter:retweets means containing the query and filtering out retweets
		query.setResultType(ofxTwitter::SearchQuery::ResultType::MIXED);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
	}
	if (btn10.inside(x, y)) {
		std::cout << "Bath Spa University Within 10 miles" << std::endl;
		ofxTwitter::SearchQuery query("Bath Spa University");
		query.setGeoCode(51.3758, -2.3599, 10, ofxTwitter::SearchQuery::UNITS_MILES);
		query.setCount(1);
		query.setLanguage("en");
		client.search(query);
		std::cout << "Bath Spa University Within 10 miles" << std::endl;
	}
}


