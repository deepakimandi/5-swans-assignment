#include <iostream>
#include <fstream>
#include "flatbuffers/flatbuffers.h"
#include "client_generated.h"

using namespace MySchema;

void encodePerson(flatbuffers::FlatBufferBuilder& builder, const char* name, short age, float weight, Gender gender) {
    auto person_name = builder.CreateString(name);
    auto person = CreatePerson(builder, person_name, age, weight, gender);
    auto client_person = CreateClient(builder, true, person, 0);
    builder.Finish(client_person);
}

void encodeGroup(flatbuffers::FlatBufferBuilder& builder, const char* groupName, const std::vector<const char*>& names, float avgAge, float avgWeight) {
    auto group_name = builder.CreateString(groupName);
    std::vector<flatbuffers::Offset<flatbuffers::String>> nameOffsets;
    
    for (const char* name : names) {
      nameOffsets.push_back(builder.CreateString(name));
    }

    auto group = CreateGroup(builder, group_name, avgAge, avgWeight, builder.CreateVector(nameOffsets));
    auto client_group = CreateClient(builder, false, 0, group);
    builder.Finish(client_group);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <path-to-fb_bytes.bin>" << std::endl;
      return 1;
    }

    const char* filename = argv[1];
    std::ofstream outfile(filename, std::ios::binary);

    flatbuffers::FlatBufferBuilder builder;

    // Encode a Person
    encodePerson(builder, "Rama", 25, 93.5, Gender::Gender_Male);
    int message_length_person_0 = builder.GetSize();
    outfile.write(reinterpret_cast<const char*>(&message_length_person_0), sizeof(int));
    outfile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), message_length_person_0);

    builder.Clear();

    // Encode a Person
    encodePerson(builder, "Seetha", 18, 62.5, Gender::Gender_Female);
    int message_length_person_1 = builder.GetSize();
    outfile.write(reinterpret_cast<const char*>(&message_length_person_1), sizeof(int));
    outfile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), message_length_person_1);

    builder.Clear();

    // Encode a Group
    std::vector<const char*> groupNames = {"Ram", "Shayam", "Raghuveer"};
    encodeGroup(builder, "FightClub", groupNames, 24.5, 66);
    int message_length_group = builder.GetSize();
    outfile.write(reinterpret_cast<const char*>(&message_length_group), sizeof(int));
    outfile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), message_length_group);

    outfile.close();

    std::cout << "Encoded clients data and saved to " << filename << std::endl;

    return 0;
}
