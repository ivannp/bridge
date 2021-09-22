#include <dds/dll.h>

#include "ddsjson.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

static char * ErrorToJson(const char * error)
{
  StringBuffer sb;
  Writer<StringBuffer> writer(sb);

  writer.StartObject();

  writer.Key("error");
  writer.String(error);

  writer.EndObject();

  return strdup(sb.GetString());
}

static char * TableResultToJson(const ddTableResults * table)
{
  StringBuffer sb;
  Writer<StringBuffer> writer(sb);

  writer.StartObject();

  const string spades = "spades";
  const string hearts = "hearts";
  const string diamonds = "diamonds";
  const string clubs = "clubs";
  const string nt = "notrump";

  writer.Key("north");
  writer.StartObject();
  writer.Key(spades.data());
  writer.Int(table->resTable[0][0]);
  writer.Key(hearts.data());
  writer.Int(table->resTable[1][0]);
  writer.Key(diamonds.data());
  writer.Int(table->resTable[2][0]);
  writer.Key(clubs.data());
  writer.Int(table->resTable[3][0]);
  writer.Key(nt.data());
  writer.Int(table->resTable[4][0]);
  writer.EndObject();

  writer.Key("east");
  writer.StartObject();
  writer.Key(spades.data());
  writer.Int(table->resTable[0][1]);
  writer.Key(hearts.data());
  writer.Int(table->resTable[1][1]);
  writer.Key(diamonds.data());
  writer.Int(table->resTable[2][1]);
  writer.Key(clubs.data());
  writer.Int(table->resTable[3][1]);
  writer.Key(nt.data());
  writer.Int(table->resTable[4][1]);
  writer.EndObject();

  writer.Key("south");
  writer.StartObject();
  writer.Key(spades.data());
  writer.Int(table->resTable[0][2]);
  writer.Key(hearts.data());
  writer.Int(table->resTable[1][2]);
  writer.Key(diamonds.data());
  writer.Int(table->resTable[2][2]);
  writer.Key(clubs.data());
  writer.Int(table->resTable[3][2]);
  writer.Key(nt.data());
  writer.Int(table->resTable[4][2]);
  writer.EndObject();

  writer.Key("west");
  writer.StartObject();
  writer.Key(spades.data());
  writer.Int(table->resTable[0][3]);
  writer.Key(hearts.data());
  writer.Int(table->resTable[1][3]);
  writer.Key(diamonds.data());
  writer.Int(table->resTable[2][3]);
  writer.Key(clubs.data());
  writer.Int(table->resTable[3][3]);
  writer.Key(nt.data());
  writer.Int(table->resTable[4][3]);
  writer.EndObject();

  writer.EndObject();

  return strdup(sb.GetString());
}

void FreeMemory(void * p)
{
  free(p);
}

char * CalcAllTablesJson(const char * params)
{
  Document jobj;
  jobj.Parse(params);

  ddTableDealsPBN pbnDeals;
  pbnDeals.noOfTables = 1;
  strcpy(pbnDeals.deals[0].cards, jobj["pbn"].GetString());

  ddTablesRes table;
  allParResults pres;

  int mode = 0; // No par calculation
  int trumpFilter[DDS_STRAINS] = {0, 0, 0, 0, 0}; // All
  int res = CalcAllTablesPBN(&pbnDeals, 0, trumpFilter, &table, &pres);

  if (res != RETURN_NO_FAULT)
  {
    char line[80];
    ErrorMessage(res, line);
    return ErrorToJson(line);
  }

  return TableResultToJson(&table.results[0]);
}
