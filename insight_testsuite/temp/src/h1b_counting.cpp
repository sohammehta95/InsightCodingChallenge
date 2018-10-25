
//CPP

//============================================================================
// Name        : soham.cpp
// Author      : Soham
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <map>
#include<set>
#include <fstream>
#include<queue>
#include <string.h>
#include <list>
#include <sstream>
#include <unistd.h>

using namespace std;

class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ';'))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}


map<string,string> makeNames()
{
	map<string,string> name;
	name["ALABAMA"]="AL";
	name["ALASKA"]="AK";
	name["ARIZONA"]="AZ";
	name["ARKANSAS"]="AR";
	name["CALIFORNIA"]="CA";
	name["COLORADO"]="CO";
	name["CONNECTICUT"]="CT";
	name["DELAWARE"]="DE";
	name["FLORIDA"]="FL";
	name["GEORGIA"]="GA";
	name["HAWAII"]="HI";
	name["IDAHO"]="ID";
	name["ILLINOIS"]="IL";
	name["INDIANA"]="IN";
	name["IOWA"]="IA";
	name["KANSAS"]="KS";
	name["KENTUCKY"]="KY";
	name["LOUISIANA"]="LA";
	name["MAINE"]="ME";
	name["MARYLAND"]="MD";
	name["MASSACHUSETTS"]="MA";
	name["MICHIGAN"]="MI";
	name["MINNESOTA	"]="MN";
	name["MISSISSIPPI"]="MS";
	name["MISSOURI"]="MO";
	name["MONTANA"]="MT";
	name["NEBRASKA"]="NE";
	name["NEVADA"]="NV";
	name["NEW HAMPSHIRE"]="NH";
	name["NEW JERSEY"]="NJ";
	name["NEW MEXICO"]="NM";
	name["NEW YORK"]="NY";
	name["NORTH CAROLINA"]="NC";
	name["NORTH DAKOTA"]="ND";
	name["OHIO"]="OH";
	name["OKLAHOMA"]="OK";
	name["OREGON"]="OR";
	name["PENNSYLVANIA"]="PA";
	name["RHODE ISLAND"]="RI";
	name["SOUTH CAROLINA"]="SC";
	name["SOUTH DAKOTA"]="SD";
	name["TENNESSEE"]="TN";
	name["TEXAS"]="TX";
	name["UTAH"]="UT";
	name["VERMONT"]="VT";
	name["VIRGINIA"]="VA";
	name["WASHINGTON"]="WA";
	name["WEST VIRGINIA"]="WV";
	name["WISCONSIN"]="WI";
	name["WYOMING"]="WY";

	return name;
}

struct comparator{
	bool operator()(const pair<string,int> &A, const pair<string,int> &B)
	{
		if(A.second==B.second)
			return strcmp(A.first.c_str(), B.first.c_str()) < 0;

		return A.second>B.second; //Min Heap
	}
};

string prd(const double x, const int decDigits) {
    stringstream ss;
    ss << fixed;
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}


int main(int argc, char *argv[])
{
//	 char buf[255];
//	 getcwd(buf, sizeof(buf));
//	 cout << "Current working directory is " << buf << endl;

	string inputPath(argv[1]);

	std::ifstream file(inputPath);

	CSVRow row;

	bool checkRow = true;

	int caseSt = -1;
	int socName = -1;
	long long int totalCases = 0;

	int workState = -1;
	map<string,string> name = makeNames();

	//For Occupation
	unordered_map<string,int> m;
	priority_queue< pair<string,int> , vector<pair<string,int> >,comparator> pq; //Min Heap


	//For Work State
	unordered_map<string,int> m2;
	priority_queue< pair<string,int> , vector<pair<string,int> >,comparator> pq2; //Min Heap

	while(file >> row)
	{
		if(checkRow)
		{
			vector<string> curr = row.m_data;
			for(int i=0;i<curr.size();i++)
			{
				if(curr[i]=="CASE_STATUS" || curr[i]=="STATUS" || curr[i]=="Case_No")
					caseSt = i;

				if(curr[i]=="SOC_NAME"  || curr[i]=="LCA_CASE_SOC_NAME" || curr[i]=="Occupational_Title")
					socName = i;

				if(curr[i]=="WORKSITE_STATE" || curr[i]=="LCA_CASE_WORKLOC1_STATE" || curr[i]=="LCA_CASE_WORKLOC2_STATE" || curr[i]=="State_1" || curr[i]=="State_2")
					workState = i;


				if(caseSt!=-1 && socName!=-1 && workState!=-1)
					break;
			}

			if(caseSt==-1 || socName==-1 || workState==-1)
			{
				cout<<"One of the Column Name was not recognizable. Kindly check the File Structure Docs to update column names"<<endl;
				return 0;
			}

			//cout<<caseSt<<"    "<<socName<<"   "<<workState<<endl;
			checkRow = false;
			continue;
		}

		totalCases++;



		string currSocName = row[socName];
		if ( currSocName.front() == '"' )
		{
			currSocName.erase( 0, 1 ); // erase the first character
			currSocName.erase( currSocName.size() - 1 ); // erase the last character
		}

		string currWorkState = row[workState];

		if(name.find(currWorkState)!=name.end())
			currWorkState = name[currWorkState];

//		if ( currWorkState.front() == '"' )
//		{
//			currWorkState.erase( 0, 1 ); // erase the first character
//			currWorkState.erase( currWorkState.size() - 1 ); // erase the last character
//		}


		if(row[caseSt] == "CERTIFIED"){
			m[currSocName]++;
			m2[currWorkState]++;
		}
		else{
			m[currSocName];
			m2[currWorkState];
		}


	}





	//*********************           Occupation      ************//

	for(auto mSoc: m)
		{
			pair<string,int> p = make_pair(mSoc.first,mSoc.second);
			if(pq.size()<10)
				pq.push(p);
			else
			{
				if(pq.top().second<mSoc.second)
				{
					pq.pop();
					pq.push(p);
				}
			}

		}


	vector<string> result;

	while(!pq.empty())
	{
		auto p = pq.top();
		pq.pop();
		double percentage = (double)p.second*100/totalCases;

		string per = prd(percentage,1);

		string s = p.first+";"+to_string(p.second)+";"+ per+"%";
		result.push_back(s);

	}
	result.push_back("TOP_OCCUPATIONS;NUMBER_CERTIFIED_APPLICATIONS;PERCENTAGE");

	ofstream textfile;

 	
	string outputPath1(argv[2]);

	textfile.open (outputPath1);

	for(int i=result.size()-1;i>=0;i--)
		textfile << result[i] << endl;

	textfile.close();

	//*******************    State      ************//


	for(auto mState: m2)
		{
			pair<string,int> p = make_pair(mState.first,mState.second);
			if(pq2.size()<10)
				pq2.push(p);
			else
			{
				if(pq2.top().second<mState.second)
				{
					pq2.pop();
					pq2.push(p);
				}

			}

		}



	vector<string> result2;
	while(!pq2.empty())
	{
		auto p = pq2.top();
		pq2.pop();
		double percentage = (double)p.second*100/totalCases;

		string per = prd(percentage,1);

		string s = p.first+";"+to_string(p.second)+";"+ per+"%";
		result2.push_back(s);

	}
	result2.push_back("TOP_STATES;NUMBER_CERTIFIED_APPLICATIONS;PERCENTAGE");

	ofstream textfile2;

	string outputPath2(argv[3]);
	textfile2.open (outputPath2);

	for(int i=result2.size()-1;i>=0;i--)
			textfile2 << result2[i] << endl;

	textfile2.close();


  return 0;
}
