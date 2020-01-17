constexpr s32 UNICODE_NUMBER_OFFSET = 48;

constexpr bool debug_output = false;

template<typename... Args>
inline
void debug_log(const char* message, Args... args)
{
#if debug_output
	printf(message, args...);
#endif
}

enum class instruction_type : s32 {
	add = 1,
	multiply = 2,
	user_input = 3,
	output = 4,
	terminate_program = 99
};

enum class parameter_mode : s32 {
	position = 0,
	immediate = 1
};

inline
s32 IntcodeComputer(const intcodeArr inputArr)
{
	intcodeArr arr;
	arr.Length = inputArr.Length * inputArr.Length;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * arr.Length));

	memset(arr.Data, 0, sizeof(s32) * arr.Length);
	memcpy(arr.Data, inputArr.Data, sizeof(s32) * inputArr.Length);

	char instruction[sizeof(instruction_type) * 64];
	instruction_type opcode;
	parameter_mode parameterModes[sizeof(parameter_mode) * 64];

	for (auto i = 0; i < arr.Length;)
	{
		// Reset memory
		memset(parameterModes, 0, (s32)64);

		// Read instruction
		sprintf(instruction, "%i", arr[i]);
		s32 instruction_length = 0;

		while (instruction[instruction_length] != '\0')
			instruction_length++;		

		if (instruction_length <= 0)
			throw std::length_error("invalid instruction");
		else if (instruction_length == 1)
			opcode = instruction_type(instruction[0] - UNICODE_NUMBER_OFFSET);
		else
		{
			auto left = (instruction[instruction_length - 2] - UNICODE_NUMBER_OFFSET) * 10;
			auto right = instruction[instruction_length - 1] - UNICODE_NUMBER_OFFSET;
			opcode = instruction_type(left + right);
		}

		s32 parameterModes_length = instruction_length > 2 ? instruction_length - 2 : 0;
		for (s32 j = 0; j < parameterModes_length; ++j)
		{
			auto val = instruction[(parameterModes_length - 1) - j];
			parameterModes[j] = parameter_mode(val - UNICODE_NUMBER_OFFSET);
		}

		debug_log(">>> %s = opcode: %i\n", instruction, opcode);

		debug_log("[modes]");
		for (s32 j = 0; j < parameterModes_length; ++j)
			debug_log(" %i", parameterModes[j]);
		debug_log("\n");

		switch (opcode)
		{
			case instruction_type::terminate_program:
				return arr[0];
			case instruction_type::add:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i, %i, %i\n", parameter0, parameter1, parameter2);

				auto val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				auto val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				debug_log("[wrtng] val: '%i' to position: '%i'\n", val0 + val1, parameter2);
				arr[parameter2] = val0 + val1;

				i += 4;
				break;
			}
			case instruction_type::multiply:
			{
				s32 parameter0 = arr[i + 1];
				s32 parameter1 = arr[i + 2];
				s32 parameter2 = arr[i + 3]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i, %i, %i\n", parameter0, parameter1, parameter2);

				auto val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				auto val1 = parameterModes[1] == parameter_mode::position ? arr[parameter1] : parameter1;

				debug_log("[wrtng] val: '%i' to position: '%i'\n", val0 * val1, parameter2);
				arr[parameter2] = val0 * val1;

				i += 4;
				break;
			}
			case instruction_type::user_input:
			{
				s32 parameter0 = arr[i + 1]; // Parameters that an instruction writes to will never be in imediate mode
				debug_log("[param] %i\n", parameter0);

				s32 inputVal;
				printf("[input] Enter ID: ");
				if (scanf("%d", &inputVal) == NULL)
				{
					printf("[Excep] Invalid input", opcode);
					return -1;
				}

				debug_log("[wrtng] val: '%i' to position: '%i'\n", inputVal, parameter0);
				arr[parameter0] = inputVal;

				i += 2;
				break;
			}
			case instruction_type::output:
			{
				s32 parameter0 = arr[i + 1];
				debug_log("[param] %i\n", parameter0);

				s32 val0 = parameterModes[0] == parameter_mode::position ? arr[parameter0] : parameter0;
				printf("[outpt] %i\n", val0);

				i += 2; //?
				break;
			}
			default:
			{
				debug_log("[Excep] Opcode %i does not exist", opcode);
				return -1;
			}
		}
		debug_log("\n");
	}
}

intcodeArr ReadIntcodeInput(string input)
{
	char* buffer = new char[4]{ 0, 0, 0, '\0' };
	s32 buffer_length = 0;

	intcodeArr arr;
	arr.Length = 0;
	arr.Data = reinterpret_cast<s32*>(malloc(sizeof(s32) * (1024 + 1)));

	for (s32 i = 0; i < input.Length; i++)
	{
		s32 c = input[i];
		if (c == COMMA || c == EOF)
		{
			s32 num = atoi(buffer);
			arr[arr.Length] = num;
			arr.Length++;

			memset(buffer, 0, buffer_length);
			buffer_length = 0;

			if (c == EOF)
				break;
		}
		else
		{
			char num_part = (char)c;
			buffer[buffer_length] = num_part;
			buffer_length++;
		}
	}

	return arr;
}
