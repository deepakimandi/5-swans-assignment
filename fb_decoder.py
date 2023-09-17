import sys
import struct
import flatbuffers
from MySchema.Client import Client
from MySchema.Gender import Gender

def decode_person(person):
    gender_str = "Male" if person.Gender() == Gender.Male else "Female"
    return f"{person.Name().decode('utf-8')}, {person.Age()}, {person.Weight()}, {gender_str}"

def decode_group(group):
    names = [group.ListOfNames(j).decode('utf-8') for j in range(group.ListOfNamesLength())]
    names_str = ", ".join(names)
    return f"{group.GroupName().decode('utf-8')}, {group.AverageAge()}, {group.AverageWeight()}, {{{names_str}}}"

def decode_client(client, message_number):
    if client.IsPerson():
        return f"{message_number}. {{{decode_person(client.Person())}}}"
    else:
        return f"{message_number}. {{{decode_group(client.Group())}}}"

def main():
    if len(sys.argv) != 2:
        print("Usage: fb_decoder.py <path-to-fb_bytes.bin>")
        sys.exit(1)

    input_file = sys.argv[1]

    with open(input_file, 'rb') as f:
        data = f.read()

    pos = 0
    message_number = 1

    while pos < len(data):
        message_length = struct.unpack("<I", data[pos:pos+4])[0]
        pos += 4

        message_data = data[pos:pos+message_length]
        pos += message_length

        client = Client.GetRootAsClient(message_data, 0)
        decoded_client = decode_client(client, message_number)

        print(decoded_client)

        message_number += 1

if __name__ == "__main__":
    main()
