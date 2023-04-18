#pragma once

#include <iostream>
#include <vector>
#include <typeinfo>

// Helpful Functions library
namespace HFL {

// converts std::type_info to a more readable std::string
// usage: 
// readTypeid(typeid(...).name())
// extraInfo: if true, returns extra information about the type when present
// NOTE: ONLY FOR GCC AS OF RIGHT NOW
std::string readTypeid (
	const std::type_info& type, 
	const bool& extraInfo = false
) {
	// loopup table for types
	std::vector<std::pair<std::string,std::string>> namesLookup {
		{"v",  "void"              },
		{"w",  "wchar_t"           },
		{"b",  "bool"              },
		{"c",  "char"              },
		{"a",  "signed char"       },
		{"h",  "unsigned char"     },
		{"s",  "short"             },
		{"t",  "unsigned short"    },
		{"i",  "int"               },
		{"j",  "unsigned int"      },
		{"l",  "long"              },
		{"m",  "unsigned long"     },
		{"x",  "long long"         },
		{"y",  "unsigned long long"},
		{"n",  "__int128"          },
		{"o",  "unsigned __int128" },
		{"f",  "float"             },
		{"d",  "double"            },
		{"e",  "long double"       },
		{"g",  "__float128"        },
		{"z",  "ellipsis"          },
		{"Di", "char32_t"          },
		{"Ds", "char16_t"          },
		{"Du", "char8_t"           },
		{"Da", "auto"              },
		{"Dc", "decltype(auto)"    },
		{"Dn", "std::nullptr_t"    }
	};

	std::string temp = std::string(type.name());
	if (temp.size() > 10) 
		if (temp.substr(0, 10) == "St6vectorI") 
			return "std::vector";

	for (auto x : namesLookup) 
		if (temp == x.first) return x.second;

	if (type == typeid(std::string)) 
		return "std::string";

	return "unknown";
}

// converts an ingeter into the corresponding MCI error
std::string mciErrorLookup(int error) {
	switch (error) {
		case 257: return "MCIERR_INVALID_DEVICE_ID";
		case 258: return "MCIERR_UNRECOGNIZED_KEYWORD";
		case 259: return "MCIERR_UNRECOGNIZED_COMMAND";
		case 260: return "MCIERR_HARDWARE";
		case 261: return "MCIERR_INVALID_DEVICE_NAME";
		case 262: return "MCIERR_OUT_OF_MEMORY";
		case 263: return "MCIERR_DEVICE_OPEN";
		case 264: return "MCIERR_CANNOT_LOAD_DRIVER";
		case 265: return "MCIERR_MISSING_COMMAND_STRING";
		case 266: return "MCIERR_PARAM_OVERFLOW";
		case 267: return "MCIERR_MISSING_STRING_ARGUMENT";
		case 268: return "MCIERR_BAD_INTEGER";
		case 269: return "MCIERR_PARSER_INTERNAL";
		case 270: return "MCIERR_DRIVER_INTERNAL";
		case 271: return "MCIERR_MISSING_PARAMETER";
		case 272: return "MCIERR_UNSUPPORTED_FUNCTION";
		case 273: return "MCIERR_FILE_NOT_FOUND";
		case 274: return "MCIERR_DEVICE_NOT_READY";
		case 275: return "MCIERR_INTERNAL";
		case 276: return "MCIERR_DRIVER";
		case 277: return "MCIERR_CANNOT_USE_ALL";
		case 278: return "MCIERR_MULTIPLE";
		case 279: return "MCIERR_EXTENSION_NOT_FOUND";
		case 280: return "MCIERR_OUTOFRANGE";
		case 281: return "MCIERR_FLAGS_NOT_COMPATIBLE";
		case 282: return "MCIERR_FILE_NOT_SAVED";
		case 283: return "MCIERR_DEVICE_TYPE_REQUIRED";
		case 284: return "MCIERR_DEVICE_LOCKED";
		case 286: return "MCIERR_DUPLICATE_ALIAS";
		case 287: return "MCIERR_BAD_CONSTANT";
		case 288: return "MCIERR_MUST_USE_SHAREABLE";
		case 289: return "MCIERR_MISSING_DEVICE_NAME";
		case 290: return "MCIERR_BAD_TIME_FORMAT";
		case 291: return "MCIERR_NO_CLOSING_QUOTE";
		case 292: return "MCIERR_DUPLICATE_FLAGS";
		case 293: return "MCIERR_INVALID_FILE";
		case 294: return "MCIERR_NULL_PARAMETER_BLOCK";
		case 295: return "MCIERR_UNNAMED_RESOURCE";
		case 296: return "MCIERR_NEW_REQUIRES_ALIAS";
		case 297: return "MCIERR_NOTIFY_ON_AUTO_OPEN";
		case 298: return "MCIERR_NO_ELEMENT_ALLOWED";
		case 299: return "MCIERR_NONAPPLICABLE_FUNCTION";
		case 300: return "MCIERR_ILLEGAL_FOR_AUTO_OPEN";
		case 301: return "MCIERR_FILENAME_REQUIRED";
		case 302: return "MCIERR_EXTRA_CHARACTERS";
		case 303: return "MCIERR_DEVICE_NOT_INSTALLED";
		case 304: return "MCIERR_GET_CD";
		case 305: return "MCIERR_SET_CD";
		case 306: return "MCIERR_SET_DRIVE";
		case 307: return "MCIERR_DEVICE_LENGTH";
		case 308: return "MCIERR_DEVICE_ORD_LENGTH";
		case 309: return "MCIERR_NO_INTEGER";
		case 310: return "MCIERR_WAVE_OUTPUTSINUSE";
		case 311: return "MCIERR_WAVE_SETOUTPUTINUSE";
		case 312: return "MCIERR_WAVE_INPUTSINUSE";
		case 313: return "MCIERR_WAVE_SETINPUTINUSE";
		case 314: return "MCIERR_WAVE_OUTPUTUNSPECIFIED";
		case 315: return "MCIERR_WAVE_INPUTUNSPECIFIED";
		case 316: return "MCIERR_WAVE_OUTPUTSUNSUITABLE";
		case 317: return "MCIERR_WAVE_SETOUTPUTUNSUITABLE";
		case 318: return "MCIERR_WAVE_INPUTSUNSUITABLE";
		case 319: return "MCIERR_WAVE_SETINPUTUNSUITABLE";
		case 320: return "MCIERR_SEQ_DIV_INCOMPATIBLE";
		case 321: return "MCIERR_SEQ_PORT_INUSE";
		case 322: return "MCIERR_SEQ_PORT_NONEXISTENT";
		case 323: return "MCIERR_SEQ_PORT_MAPNODEVICE";
		case 324: return "MCIERR_SEQ_PORT_MISCERROR";
		case 325: return "MCIERR_SEQ_TIMER";
		case 326: return "MCIERR_SEQ_PORTUNSPECIFIED";
		case 327: return "MCIERR_SEQ_NOMIDIPRESENT";
		case 328: return "MCIERR_NO_WINDOW";
		case 329: return "MCIERR_CREATEWINDOW";
		case 330: return "MCIERR_FILE_READ";
		case 331: return "MCIERR_FILE_WRITE";
		case 332: return "MCIERR_NO_IDENTITY";
		case 333: return "MCIERR_CUSTOM_DRIVER_BASE";
	}
	return "unknown error";
}

// terminal ASCII colors
namespace TermColors 
{
	std::string reset   = "\u001b[0m";

	// normal

	std::string black   = "\u001b[30m";
	std::string red     = "\u001b[31m";
	std::string green   = "\u001b[32m";
	std::string yellow  = "\u001b[33m";
	std::string blue    = "\u001b[34m";
	std::string magenta = "\u001b[35m";
	std::string cyan    = "\u001b[36m";
	std::string white   = "\u001b[37m";

	// bright
	// sometimes doesnt work

	std::string BRI_black   = "\u001b[30m;1m";
	std::string BRI_red     = "\u001b[31m;1m";
	std::string BRI_green   = "\u001b[32m;1m";
	std::string BRI_yellow  = "\u001b[33m;1m";
	std::string BRI_blue    = "\u001b[34m;1m";
	std::string BRI_magenta = "\u001b[35m;1m";
	std::string BRI_cyan    = "\u001b[36m;1m";
	std::string BRI_white   = "\u001b[37m;1m";

	// backgrounds

	std::string BACK_black   = "\u001b[40m";
	std::string BACK_red     = "\u001b[41m";
	std::string BACK_green   = "\u001b[42m";
	std::string BACK_yellow  = "\u001b[43m";
	std::string BACK_blue    = "\u001b[44m";
	std::string BACK_magenta = "\u001b[45m";
	std::string BACK_cyan    = "\u001b[46m";
	std::string BACK_white   = "\u001b[47m";

	// bright backgrounds
	// sometimes doesnt work

	std::string BRI_BACK_black   = "\u001b[40m;1m";
	std::string BRI_BACK_red     = "\u001b[41m;1m";
	std::string BRI_BACK_green   = "\u001b[42m;1m";
	std::string BRI_BACK_yellow  = "\u001b[43m;1m";
	std::string BRI_BACK_blue    = "\u001b[44m;1m";
	std::string BRI_BACK_magenta = "\u001b[45m;1m";
	std::string BRI_BACK_cyan    = "\u001b[46m;1m";
	std::string BRI_BACK_white   = "\u001b[47m;1m";

	// others

	std::string BOLD   = "\u001b[1m";
	std::string UNDERL = "\u001b[4m";
	std::string REVRSD = "\u001b[7m";
}

// periodic table
static const std::vector<std::vector<std::string>> periodicTable 
{
	{"1.0079"  , "Hydrogen"      , "H" , "1"  },
	{"4.00260" , "Helium"        , "He", "2"  },
	{"6.941"   , "Lithium"       , "Li", "3"  },
	{"9.0122"  , "Beryllium"     , "Be", "4"  },
	{"10.811"  , "Boron"         , "B" , "5"  },
	{"12.0107" , "Carbon"        , "C" , "6"  },
	{"14.0067" , "Nitrogen"      , "N" , "7"  },
	{"15.9994" , "Oxygen"        , "O" , "8"  },
	{"18.9984" , "Fluorine"      , "F" , "9"  },
	{"20.1797" , "Neon"          , "Ne", "10" },
	{"22.9897" , "Sodium"        , "Na", "11" },
	{"24.305"  , "Magnesium"     , "Mg", "12" },
	{"26.9815" , "Aluminum"      , "Al", "13" },
	{"28.0855" , "Silicon"       , "Si", "14" },
	{"30.9738" , "Phosphorus"    , "P" , "15" },
	{"32.065"  , "Sulfur"        , "S" , "16" },
	{"35.453"  , "Chlorine"      , "Cl", "17" },
	{"39.0983" , "Potassium"     , "K" , "19" },
	{"39.948"  , "Argon"         , "Ar", "18" },
	{"40.078"  , "Calcium"       , "Ca", "20" },
	{"44.9559" , "Scandium"      , "Sc", "21" },
	{"47.867"  , "Titanium"      , "Ti", "22" },
	{"50.9415" , "Vanadium"      , "V" , "23" },
	{"51.9961" , "Chromium"      , "Cr", "24" },
	{"54.938"  , "Manganese"     , "Mn", "25" },
	{"55.845"  , "Iron"          , "Fe", "26" },
	{"58.6934" , "Nickel"        , "Ni", "28" },
	{"58.9332" , "Cobalt"        , "Co", "27" },
	{"63.546"  , "Copper"        , "Cu", "29" },
	{"65.39"   , "Zinc"          , "Zn", "30" },
	{"69.723"  , "Gallium"       , "Ga", "31" },
	{"72.64"   , "Germanium"     , "Ge", "32" },
	{"74.9216" , "Arsenic"       , "As", "33" },
	{"78.96 "  , "Selenium"      , "Se", "34" },
	{"79.904"  , "Bromine"       , "Br", "35" },
	{"83.8"    , "Krypton"       , "Kr", "36" },
	{"85.4678" , "Rubidium"      , "Rb", "37" },
	{"87.62"   , "Strontium"     , "Sr", "38" },
	{"88.9059" , "Yttrium"       , "Y" , "39" },
	{"91.224"  , "Zirconium"     , "Zr", "40" },
	{"92.9064" , "Niobium"       , "Nb", "41" },
	{"95.94"   , "Molybdenum"    , "Mo", "42" },
	{"98"      , "Technetium"    , "Tc", "43" },
	{"101.07"  , "Ruthenium"     , "Ru", "44" },
	{"102.905" , "Rhodium"       , "Rh", "45" },
	{"106.42"  , "Palladium"     , "Pd", "46" },
	{"107.868" , "Silver"        , "Ag", "47" },
	{"112.411" , "Cadmium"       , "Cd", "48" },
	{"114.818" , "Indium"        , "In", "49" },
	{"118.71"  , "Tin"           , "Sn", "50" },
	{"121.76"  , "Antimony"      , "Sb", "51" },
	{"126.904" , "Iodine"        , "I" , "53" },
	{"127.6"   , "Tellurium"     , "Te", "52" },
	{"131.293" , "Xenon"         , "Xe", "54" },
	{"132.905" , "Cesium"        , "Cs", "55" },
	{"137.327" , "Barium"        , "Ba", "56" },
	{"138.905" , "Lanthanum"     , "La", "57" },
	{"140.116" , "Cerium"        , "Ce", "58" },
	{"140.907" , "Praseodymium"  , "Pr", "59" },
	{"144.24"  , "Neodymium"     , "Nd", "60" },
	{"145"     , "Promethium"    , "Pm", "61" },
	{"150.36"  , "Samarium"      , "Sm", "62" },
	{"151.964" , "Europium"      , "Eu", "63" },
	{"157.25"  , "Gadolinium"    , "Gd", "64" },
	{"158.925" , "Terbium"       , "Tb", "65" },
	{"162.5"   , "Dysprosium"    , "Dy", "66" },
	{"164.930" , "Holmium"       , "Ho", "67" },
	{"167.259" , "Erbium"        , "Er", "68" },
	{"168.934" , "Thulium"       , "Tm", "69" },
	{"173.04"  , "Ytterbium"     , "Yb", "70" },
	{"174.967" , "Lutetium"      , "Lu", "71" },
	{"178.49"  , "Hafnium"       , "Hf", "72" },
	{"180.947" , "Tantalum"      , "Ta", "73" },
	{"183.84"  , "Tungsten"      , "W" , "74" },
	{"186.207" , "Rhenium"       , "Re", "75" },
	{"190.23"  , "Osmium"        , "Os", "76" },
	{"192.217" , "Iridium"       , "Ir", "77" },
	{"195.078" , "Platinum"      , "Pt", "78" },
	{"196.966" , "Gold"          , "Au", "79" },
	{"200.59"  , "Mercury"       , "Hg", "80" },
	{"204.383" , "Thallium"      , "Tl", "81" },
	{"207.2"   , "Lead"          , "Pb", "82" },
	{"208.980" , "Bismuth"       , "Bi", "83" },
	{"209"     , "Polonium"      , "Po", "84" },
	{"210"     , "Astatine"      , "At", "85" },
	{"222"     , "Radon"         , "Rn", "86" },
	{"223"     , "Francium"      , "Fr", "87" },
	{"226"     , "Radium"        , "Ra", "88" },
	{"227"     , "Actinium"      , "Ac", "89" },
	{"231.035" , "Protactinium"  , "Pa", "91" },
	{"232.038" , "Thorium"       , "Th", "90" },
	{"237"     , "Neptunium"     , "Np", "93" },
	{"238.028" , "Uranium"       , "U" , "92" },
	{"243"     , "Americium"     , "Am", "95" },
	{"244"     , "Plutonium"     , "Pu", "94" },
	{"247"     , "Curium"        , "Cm", "96" },
	{"247"     , "Berkelium"     , "Bk", "97" },
	{"251"     , "Californium"   , "Cf", "98" },
	{"252"     , "Einsteinium"   , "Es", "99" },
	{"257"     , "Fermium"       , "Fm", "100"},
	{"258"     , "Mendelevium"   , "Md", "101"},
	{"259"     , "Nobelium"      , "No", "102"},
	{"261"     , "Rutherfordium" , "Rf", "104"},
	{"262"     , "Lawrencium"    , "Lr", "103"},
	{"262"     , "Dubnium"       , "Db", "105"},
	{"264"     , "Bohrium"       , "Bh", "107"},
	{"266"     , "Seaborgium"    , "Sg", "106"},
	{"268"     , "Meitnerium"    , "Mt", "109"},
	{"272"     , "Roentgenium"   , "Rg", "111"},
	{"277"     , "Hassium"       , "Hs", "108"},
	{"281"     , "Darmstadtium"  , "Ds", "110"},
	{"285"     , "Copernicium"   , "Cn", "112"},
	{"286"     , "Nihonium"      , "Nh", "113"},
	{"289"     , "Flerovium"     , "Fl", "114"},
	{"289"     , "Moscovium"     , "Mc", "115"},
	{"293"     , "Livermorium"   , "Lv", "116"},
	{"294"     , "Tennessine"    , "Ts", "117"},
	{"295.216" , "Oganesson"     , "Og", "118"}
};

}