#include"AenMath.h"


namespace Aen {

	namespace Concealed {


		// Vector static Member variables

		constexpr VecT<float, 2u> VecT<float, 2u>::zero = VecT<float, 2u>(0.f);
		constexpr VecT<float, 2u> VecT<float, 2u>::one = VecT<float, 2u>(1.f);

		constexpr VecT<int, 2u> VecT<int, 2u>::zero = VecT<int, 2u>(0);
		constexpr VecT<int, 2u> VecT<int, 2u>::one = VecT<int, 2u>(1);

		constexpr VecT<float, 3u> VecT<float, 3u>::zero = VecT<float, 3u>(0.f);
		constexpr VecT<float, 3u> VecT<float, 3u>::one = VecT<float, 3u>(1.f);

		constexpr VecT<int, 3u> VecT<int, 3u>::zero = VecT<int, 3u>(0);
		constexpr VecT<int, 3u> VecT<int, 3u>::one = VecT<int, 3u>(1);

		constexpr VecT<float, 4u> VecT<float, 4u>::zero = VecT<float, 4u>(0.f);
		constexpr VecT<float, 4u> VecT<float, 4u>::one = VecT<float, 4u>(1.f);

		constexpr VecT<int, 4u> VecT<int, 4u>::zero = VecT<int, 4u>(0);
		constexpr VecT<int, 4u> VecT<int, 4u>::one = VecT<int, 4u>(1);


		// Matrix static Member variables

		constexpr MatT<float, 3u, 3u> MatT<float, 3u, 3u>::identity = MatT<float, 3u, 3u>();

		constexpr MatT<float, 3u, 4u> MatT<float, 3u, 4u>::identity = MatT<float, 3u, 4u>();

		constexpr MatT<float, 4u, 3u> MatT<float, 4u, 3u>::identity = MatT<float, 4u, 3u>();

		constexpr MatT<float, 4u, 4u> MatT<float, 4u, 4u>::identity = MatT<float, 4u, 4u>();

	}


	// Quaternion static Member variable
		
	constexpr Quat Quat::identity = Quat();


	// Color static Member variables

	constexpr Color Color::AliceBlue            = { 0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::AntiqueWhite         = { 0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f } ;
	constexpr Color Color::Aqua                 = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Aquamarine           = { 0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f } ;
	constexpr Color Color::Azure                = { 0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Beige                = { 0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f } ;
	constexpr Color Color::Bisque               = { 1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f } ;
	constexpr Color Color::Black                = { 0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::BlanchedAlmond       = { 1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f } ;
	constexpr Color Color::Blue                 = { 0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::BlueViolet           = { 0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f } ;
	constexpr Color Color::Brown                = { 0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f } ;
	constexpr Color Color::BurlyWood            = { 0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f } ;
	constexpr Color Color::CadetBlue            = { 0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f } ;
	constexpr Color Color::Chartreuse           = { 0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::Chocolate            = { 0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f } ;
	constexpr Color Color::Coral                = { 1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f } ;
	constexpr Color Color::CornflowerBlue       = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f } ;
	constexpr Color Color::Cornsilk             = { 1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f } ;
	constexpr Color Color::Crimson              = { 0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f } ;
	constexpr Color Color::Cyan                 = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::DarkBlue             = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f } ;
	constexpr Color Color::DarkCyan             = { 0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f } ;
	constexpr Color Color::DarkGoldenrod        = { 0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f } ;
	constexpr Color Color::DarkGray             = { 0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f } ;
	constexpr Color Color::DarkGreen            = { 0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::DarkKhaki            = { 0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f } ;
	constexpr Color Color::DarkMagenta          = { 0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f } ;
	constexpr Color Color::DarkOliveGreen       = { 0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f } ;
	constexpr Color Color::DarkOrange           = { 1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::DarkOrchid           = { 0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f } ;
	constexpr Color Color::DarkRed              = { 0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::DarkSalmon           = { 0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f } ;
	constexpr Color Color::DarkSeaGreen         = { 0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f } ;
	constexpr Color Color::DarkSlateBlue        = { 0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f } ;
	constexpr Color Color::DarkSlateGray        = { 0.184313729f, 0.309803933f, 0.309803933f, 1.000000000f } ;
	constexpr Color Color::DarkTurquoise        = { 0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f } ;
	constexpr Color Color::DarkViolet           = { 0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f } ;
	constexpr Color Color::DeepPink             = { 1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f } ;
	constexpr Color Color::DeepSkyBlue          = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::DimGray              = { 0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f } ;
	constexpr Color Color::DodgerBlue           = { 0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Firebrick            = { 0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f } ;
	constexpr Color Color::FloralWhite          = { 1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f } ;
	constexpr Color Color::ForestGreen          = { 0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f } ;
	constexpr Color Color::Fuchsia              = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Gainsboro            = { 0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f } ;
	constexpr Color Color::GhostWhite           = { 0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Gold                 = { 1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::Goldenrod            = { 0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f } ;
	constexpr Color Color::Gray                 = { 0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f } ;
	constexpr Color Color::Green                = { 0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::GreenYellow          = { 0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f } ;
	constexpr Color Color::Honeydew             = { 0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f } ;
	constexpr Color Color::HotPink              = { 1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f } ;
	constexpr Color Color::IndianRed            = { 0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f } ;
	constexpr Color Color::Indigo               = { 0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f } ;
	constexpr Color Color::Ivory                = { 1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f } ;
	constexpr Color Color::Khaki                = { 0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f } ;
	constexpr Color Color::Lavender             = { 0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f } ;
	constexpr Color Color::LavenderBlush        = { 1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f } ;
	constexpr Color Color::LawnGreen            = { 0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::LemonChiffon         = { 1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f } ;
	constexpr Color Color::LightBlue            = { 0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f } ;
	constexpr Color Color::LightCoral           = { 0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f } ;
	constexpr Color Color::LightCyan            = { 0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f } ;
	constexpr Color Color::LightGreen           = { 0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f } ;
	constexpr Color Color::LightGray            = { 0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f } ;
	constexpr Color Color::LightPink            = { 1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f } ;
	constexpr Color Color::LightSalmon          = { 1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f } ;
	constexpr Color Color::LightSeaGreen        = { 0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f } ;
	constexpr Color Color::LightSkyBlue         = { 0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f } ;
	constexpr Color Color::LightSlateGray       = { 0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f } ;
	constexpr Color Color::LightSteelBlue       = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f } ;
	constexpr Color Color::LightYellow          = { 1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f } ;
	constexpr Color Color::Lime                 = { 0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::LimeGreen            = { 0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f } ;
	constexpr Color Color::Linen                = { 0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f } ;
	constexpr Color Color::Magenta              = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::Maroon               = { 0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::MediumAquamarine     = { 0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f } ;
	constexpr Color Color::MediumBlue           = { 0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f } ;
	constexpr Color Color::MediumOrchid         = { 0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f } ;
	constexpr Color Color::MediumPurple         = { 0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f } ;
	constexpr Color Color::MediumSeaGreen       = { 0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f } ;
	constexpr Color Color::MediumSlateBlue      = { 0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f } ;
	constexpr Color Color::MediumSpringGreen    = { 0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f } ;
	constexpr Color Color::MediumTurquoise      = { 0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f } ;
	constexpr Color Color::MediumVioletRed      = { 0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f } ;
	constexpr Color Color::MidnightBlue         = { 0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f } ;
	constexpr Color Color::MintCream            = { 0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f } ;
	constexpr Color Color::MistyRose            = { 1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f } ;
	constexpr Color Color::Moccasin             = { 1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f } ;
	constexpr Color Color::NavajoWhite          = { 1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f } ;
	constexpr Color Color::Navy                 = { 0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f } ;
	constexpr Color Color::OldLace              = { 0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f } ;
	constexpr Color Color::Olive                = { 0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::OliveDrab            = { 0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f } ;
	constexpr Color Color::Orange               = { 1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::OrangeRed            = { 1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::Orchid               = { 0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f } ;
	constexpr Color Color::PaleGoldenrod        = { 0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f } ;
	constexpr Color Color::PaleGreen            = { 0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f } ;
	constexpr Color Color::PaleTurquoise        = { 0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f } ;
	constexpr Color Color::PaleVioletRed        = { 0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f } ;
	constexpr Color Color::PapayaWhip           = { 1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f } ;
	constexpr Color Color::PeachPuff            = { 1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f } ;
	constexpr Color Color::Peru                 = { 0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f } ;
	constexpr Color Color::Pink                 = { 1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f } ;
	constexpr Color Color::Plum                 = { 0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f } ;
	constexpr Color Color::PowderBlue           = { 0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f } ;
	constexpr Color Color::Purple               = { 0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f } ;
	constexpr Color Color::Red                  = { 1.000000000f, 0.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::RosyBrown            = { 0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f } ;
	constexpr Color Color::RoyalBlue            = { 0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f } ;
	constexpr Color Color::SaddleBrown          = { 0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f } ;
	constexpr Color Color::Salmon               = { 0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f } ;
	constexpr Color Color::SandyBrown           = { 0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f } ;
	constexpr Color Color::SeaGreen             = { 0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f } ;
	constexpr Color Color::SeaShell             = { 1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f } ;
	constexpr Color Color::Sienna               = { 0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f } ;
	constexpr Color Color::Silver               = { 0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f } ;
	constexpr Color Color::SkyBlue              = { 0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f } ;
	constexpr Color Color::SlateBlue            = { 0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f } ;
	constexpr Color Color::SlateGray            = { 0.439215720f, 0.501960814f, 0.564705908f, 1.000000000f } ;
	constexpr Color Color::Snow                 = { 1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f } ;
	constexpr Color Color::SpringGreen          = { 0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f } ;
	constexpr Color Color::SteelBlue            = { 0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f } ;
	constexpr Color Color::Tan                  = { 0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f } ;
	constexpr Color Color::Teal                 = { 0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f } ;
	constexpr Color Color::Thistle              = { 0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f } ;
	constexpr Color Color::Tomato               = { 1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f } ;
	constexpr Color Color::Transparent          = { 0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f } ;
	constexpr Color Color::Turquoise            = { 0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f } ;
	constexpr Color Color::Violet               = { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f } ;
	constexpr Color Color::Wheat                = { 0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f } ;
	constexpr Color Color::White                = { 1.000000000f, 1.000000000f, 1.000000000f, 1.000000000f } ;
	constexpr Color Color::WhiteSmoke           = { 0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f } ;
	constexpr Color Color::Yellow               = { 1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f } ;
	constexpr Color Color::YellowGreen          = { 0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f } ;


	// Frustom static Member variable
	
	constexpr size_t Frustum::cornerCount = 8u;


	// AABB static Member varaible
	
	constexpr size_t AABB::cornerCount = 8u;


	// OBB static Member varaible
	
	constexpr size_t OBB::cornerCount = 8u;
}