/***************************************************************************************************************
 * theme.hpp
 ****************************************************************************************************************/
#pragma once

#include "imgui.h"
//=============================

#include <cstdint>
//=============================

namespace StrawPen
{
	namespace ImGuiThemes
	{
		inline ImFont* loadCustomFont(
		    const char* font_file_path = "../assets/fonts/JetBrainsMono-Regular.ttf",
		    float font_size = 20)
		{
			return nullptr;  // TODO: debug!
			ImGuiIO& io = ImGui::GetIO();
			ImFont* font = io.Fonts->AddFontFromFileTTF(font_file_path, font_size);
			return font;
		}

		ImFont* DarkRuda()
		{
			// Dark Ruda style by Raikiri from ImThemes
			ImGuiStyle& style = ImGui::GetStyle();

			style.Alpha = 1.0f;
			style.DisabledAlpha = 0.6000000238418579f;
			style.WindowPadding = ImVec2(8.0f, 8.0f);
			style.WindowRounding = 0.0f;
			style.WindowBorderSize = 1.0f;
			style.WindowMinSize = ImVec2(32.0f, 32.0f);
			style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
			style.WindowMenuButtonPosition = ImGuiDir_Left;
			style.ChildRounding = 0.0f;
			style.ChildBorderSize = 1.0f;
			style.PopupRounding = 0.0f;
			style.PopupBorderSize = 1.0f;
			style.FramePadding = ImVec2(4.0f, 3.0f);
			style.FrameRounding = 4.0f;
			style.FrameBorderSize = 0.0f;
			style.ItemSpacing = ImVec2(8.0f, 4.0f);
			style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			style.CellPadding = ImVec2(4.0f, 2.0f);
			style.IndentSpacing = 21.0f;
			style.ColumnsMinSpacing = 6.0f;
			style.ScrollbarSize = 14.0f;
			style.ScrollbarRounding = 9.0f;
			style.GrabMinSize = 10.0f;
			style.GrabRounding = 4.0f;
			style.TabRounding = 4.0f;
			style.TabBorderSize = 0.0f;
			// style.TabMinWidthForCloseButton = 0.0f;
			style.ColorButtonPosition = ImGuiDir_Right;
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

			style.Colors[ImGuiCol_Text] =
			    ImVec4(0.9490196108818054f, 0.95686274766922f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_TextDisabled] =
			    ImVec4(0.3568627536296844f, 0.4196078479290009f, 0.4666666686534882f, 1.0f);
			style.Colors[ImGuiCol_WindowBg] =
			    ImVec4(0.1098039224743843f, 0.1490196138620377f, 0.168627455830574f, 1.0f);
			style.Colors[ImGuiCol_ChildBg] =
			    ImVec4(0.1490196138620377f, 0.1764705926179886f, 0.2196078449487686f, 1.0f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f,
			                                        0.0784313753247261f, 0.9399999976158142f);
			style.Colors[ImGuiCol_Border] =
			    ImVec4(0.0784313753247261f, 0.09803921729326248f, 0.1176470592617989f, 1.0f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_FrameBg] =
			    ImVec4(0.2000000029802322f, 0.2470588237047195f, 0.2862745225429535f, 1.0f);
			style.Colors[ImGuiCol_FrameBgHovered] =
			    ImVec4(0.1176470592617989f, 0.2000000029802322f, 0.2784313857555389f, 1.0f);
			style.Colors[ImGuiCol_FrameBgActive] =
			    ImVec4(0.08627451211214066f, 0.1176470592617989f, 0.1372549086809158f, 1.0f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08627451211214066f, 0.1176470592617989f,
			                                        0.1372549086809158f, 0.6499999761581421f);
			style.Colors[ImGuiCol_TitleBgActive] =
			    ImVec4(0.0784313753247261f, 0.09803921729326248f, 0.1176470592617989f, 1.0f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
			style.Colors[ImGuiCol_MenuBarBg] =
			    ImVec4(0.1490196138620377f, 0.1764705926179886f, 0.2196078449487686f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f,
			                                            0.01960784383118153f, 0.3899999856948853f);
			style.Colors[ImGuiCol_ScrollbarGrab] =
			    ImVec4(0.2000000029802322f, 0.2470588237047195f, 0.2862745225429535f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] =
			    ImVec4(0.1764705926179886f, 0.2196078449487686f, 0.2470588237047195f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] =
			    ImVec4(0.08627451211214066f, 0.2078431397676468f, 0.3098039329051971f, 1.0f);
			style.Colors[ImGuiCol_CheckMark] =
			    ImVec4(0.2784313857555389f, 0.5568627715110779f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_SliderGrab] =
			    ImVec4(0.2784313857555389f, 0.5568627715110779f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_SliderGrabActive] =
			    ImVec4(0.3686274588108063f, 0.6078431606292725f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_Button] =
			    ImVec4(0.2000000029802322f, 0.2470588237047195f, 0.2862745225429535f, 1.0f);
			style.Colors[ImGuiCol_ButtonHovered] =
			    ImVec4(0.2784313857555389f, 0.5568627715110779f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_ButtonActive] =
			    ImVec4(0.05882352963089943f, 0.529411792755127f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.2000000029802322f, 0.2470588237047195f,
			                                       0.2862745225429535f, 0.550000011920929f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                              0.9764705896377563f, 0.800000011920929f);
			style.Colors[ImGuiCol_HeaderActive] =
			    ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_Separator] =
			    ImVec4(0.2000000029802322f, 0.2470588237047195f, 0.2862745225429535f, 1.0f);
			style.Colors[ImGuiCol_SeparatorHovered] =
			    ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f,
			           0.7799999713897705f);
			style.Colors[ImGuiCol_SeparatorActive] =
			    ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
			style.Colors[ImGuiCol_ResizeGrip] =
			    ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.25f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
			style.Colors[ImGuiCol_Tab] =
			    ImVec4(0.1098039224743843f, 0.1490196138620377f, 0.168627455830574f, 1.0f);
			style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                           0.9764705896377563f, 0.800000011920929f);
			style.Colors[ImGuiCol_TabActive] =
			    ImVec4(0.2000000029802322f, 0.2470588237047195f, 0.2862745225429535f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocused] =
			    ImVec4(0.1098039224743843f, 0.1490196138620377f, 0.168627455830574f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocusedActive] =
			    ImVec4(0.1098039224743843f, 0.1490196138620377f, 0.168627455830574f, 1.0f);
			style.Colors[ImGuiCol_PlotLines] =
			    ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
			style.Colors[ImGuiCol_PlotLinesHovered] =
			    ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogram] =
			    ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogramHovered] =
			    ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
			style.Colors[ImGuiCol_TableHeaderBg] =
			    ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
			style.Colors[ImGuiCol_TableBorderStrong] =
			    ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_TableBorderLight] =
			    ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
			style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
			style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
			style.Colors[ImGuiCol_NavHighlight] =
			    ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_NavWindowingHighlight] =
			    ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

			return nullptr;
		}

		ImFont* NightTheme()
		{
			ImGuiStyle& style = ImGui::GetStyle();

			style.WindowRounding = 5.3f;
			style.FrameRounding = 2.3f;
			style.ScrollbarRounding = 0;

			style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
			// style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
			// style.Colors[ImGuiCol_Column]                = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			// style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
			// style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
			// style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
			// style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
			// style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

			return nullptr;
		}

		ImFont* UE4()
		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.23f, 0.24f, 0.25f, 1.00f);
			colors[ImGuiCol_TabActive] = ImVec4(0.84f, 0.84f, 0.84f, 0.40f);
			colors[ImGuiCol_Tab] = ImVec4(0.4f, 0.4f, 0.4f, 0.40f);
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
			colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);  //
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);  //
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);

			return nullptr;
		};

		ImFont* VSRounded()
		{
			// Rounded Visual Studio style by RedNicStone from ImThemes
			ImGuiStyle& style = ImGui::GetStyle();

			style.Alpha = 1.0f;
			style.DisabledAlpha = 0.6000000238418579f;
			style.WindowPadding = ImVec2(8.0f, 8.0f);
			style.WindowRounding = 4.0f;
			style.WindowBorderSize = 0.0f;
			style.WindowMinSize = ImVec2(32.0f, 32.0f);
			style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
			style.WindowMenuButtonPosition = ImGuiDir_Left;
			style.ChildRounding = 0.0f;
			style.ChildBorderSize = 1.0f;
			style.PopupRounding = 4.0f;
			style.PopupBorderSize = 1.0f;
			style.FramePadding = ImVec2(4.0f, 3.0f);
			style.FrameRounding = 2.5f;
			style.FrameBorderSize = 0.0f;
			style.ItemSpacing = ImVec2(8.0f, 4.0f);
			style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			style.CellPadding = ImVec2(4.0f, 2.0f);
			style.IndentSpacing = 21.0f;
			style.ColumnsMinSpacing = 6.0f;
			style.ScrollbarSize = 11.0f;
			style.ScrollbarRounding = 2.5f;
			style.GrabMinSize = 10.0f;
			style.GrabRounding = 2.0f;
			style.TabRounding = 3.5f;
			style.TabBorderSize = 0.0f;
			// style.TabMinWidthForCloseButton = 0.0f;
			style.ColorButtonPosition = ImGuiDir_Right;
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

			style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_TextDisabled] =
			    ImVec4(0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.0f);
			style.Colors[ImGuiCol_WindowBg] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_ChildBg] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_PopupBg] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_Border] =
			    ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
			style.Colors[ImGuiCol_BorderShadow] =
			    ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
			style.Colors[ImGuiCol_FrameBg] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_FrameBgHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_FrameBgActive] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_TitleBg] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_TitleBgActive] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_TitleBgCollapsed] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_MenuBarBg] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarBg] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrab] =
			    ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] =
			    ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] =
			    ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
			style.Colors[ImGuiCol_CheckMark] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_SliderGrab] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_SliderGrabActive] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_Button] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_ButtonHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_ButtonActive] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_Header] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_HeaderHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_HeaderActive] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_Separator] =
			    ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
			style.Colors[ImGuiCol_SeparatorHovered] =
			    ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
			style.Colors[ImGuiCol_SeparatorActive] =
			    ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
			style.Colors[ImGuiCol_ResizeGrip] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_ResizeGripHovered] =
			    ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
			style.Colors[ImGuiCol_ResizeGripActive] =
			    ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
			style.Colors[ImGuiCol_Tab] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_TabHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_TabActive] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocused] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocusedActive] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_PlotLines] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_PlotLinesHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogram] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogramHovered] =
			    ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
			style.Colors[ImGuiCol_TableHeaderBg] =
			    ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
			style.Colors[ImGuiCol_TableBorderStrong] =
			    ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_TableBorderLight] =
			    ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
			style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
			style.Colors[ImGuiCol_TextSelectedBg] =
			    ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
			style.Colors[ImGuiCol_DragDropTarget] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_NavHighlight] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			style.Colors[ImGuiCol_NavWindowingHighlight] =
			    ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ModalWindowDimBg] =
			    ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
			return loadCustomFont();
		}

		ImFont* VS()
		{
			auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
			{ return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f); };

			auto& style = ImGui::GetStyle();
			ImVec4* colors = style.Colors;

			const ImVec4 bgColor = ColorFromBytes(37, 37, 38);
			const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
			const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

			const ImVec4 panelColor = ColorFromBytes(51, 51, 55);
			const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
			const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);

			const ImVec4 textColor = ColorFromBytes(255, 255, 255);
			const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
			const ImVec4 borderColor = ColorFromBytes(78, 78, 78);

			colors[ImGuiCol_Text] = textColor;
			colors[ImGuiCol_TextDisabled] = textDisabledColor;
			colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
			colors[ImGuiCol_WindowBg] = bgColor;
			colors[ImGuiCol_ChildBg] = bgColor;
			colors[ImGuiCol_PopupBg] = bgColor;
			colors[ImGuiCol_Border] = borderColor;
			colors[ImGuiCol_BorderShadow] = borderColor;
			colors[ImGuiCol_FrameBg] = panelColor;
			colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
			colors[ImGuiCol_FrameBgActive] = panelActiveColor;
			colors[ImGuiCol_TitleBg] = bgColor;
			colors[ImGuiCol_TitleBgActive] = bgColor;
			colors[ImGuiCol_TitleBgCollapsed] = bgColor;
			colors[ImGuiCol_MenuBarBg] = panelColor;
			colors[ImGuiCol_ScrollbarBg] = panelColor;
			colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
			colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
			colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
			colors[ImGuiCol_CheckMark] = panelActiveColor;
			colors[ImGuiCol_SliderGrab] = panelHoverColor;
			colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
			colors[ImGuiCol_Button] = panelColor;
			colors[ImGuiCol_ButtonHovered] = panelHoverColor;
			colors[ImGuiCol_ButtonActive] = panelHoverColor;
			colors[ImGuiCol_Header] = panelColor;
			colors[ImGuiCol_HeaderHovered] = panelHoverColor;
			colors[ImGuiCol_HeaderActive] = panelActiveColor;
			colors[ImGuiCol_Separator] = borderColor;
			colors[ImGuiCol_SeparatorHovered] = borderColor;
			colors[ImGuiCol_SeparatorActive] = borderColor;
			colors[ImGuiCol_ResizeGrip] = bgColor;
			colors[ImGuiCol_ResizeGripHovered] = panelColor;
			colors[ImGuiCol_ResizeGripActive] = lightBgColor;
			colors[ImGuiCol_PlotLines] = panelActiveColor;
			colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
			colors[ImGuiCol_PlotHistogram] = panelActiveColor;
			colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
			colors[ImGuiCol_ModalWindowDimBg] = bgColor;
			colors[ImGuiCol_DragDropTarget] = bgColor;
			colors[ImGuiCol_NavHighlight] = bgColor;
			colors[ImGuiCol_DockingPreview] = panelActiveColor;
			colors[ImGuiCol_Tab] = bgColor;
			colors[ImGuiCol_TabActive] = panelActiveColor;
			colors[ImGuiCol_TabUnfocused] = bgColor;
			colors[ImGuiCol_TabUnfocusedActive] = panelActiveColor;
			colors[ImGuiCol_TabHovered] = panelHoverColor;

			style.WindowRounding = 0.0f;
			style.ChildRounding = 0.0f;
			style.FrameRounding = 0.0f;
			style.GrabRounding = 0.0f;
			style.PopupRounding = 0.0f;
			style.ScrollbarRounding = 0.0f;
			style.TabRounding = 0.0f;

			return nullptr;
		}

		ImFont* EmbraceTheDarkness()
		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
			colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
			colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
			colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
			colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
			colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
			colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
			colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
			colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowPadding = ImVec2(8.00f, 8.00f);
			style.FramePadding = ImVec2(5.00f, 2.00f);
			style.CellPadding = ImVec2(6.00f, 6.00f);
			style.ItemSpacing = ImVec2(6.00f, 6.00f);
			style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
			style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
			style.IndentSpacing = 25;
			style.ScrollbarSize = 15;
			style.GrabMinSize = 10;
			style.WindowBorderSize = 1;
			style.ChildBorderSize = 1;
			style.PopupBorderSize = 1;
			style.FrameBorderSize = 1;
			style.TabBorderSize = 1;
			style.WindowRounding = 7;
			style.ChildRounding = 4;
			style.FrameRounding = 3;
			style.PopupRounding = 4;
			style.ScrollbarRounding = 9;
			style.GrabRounding = 3;
			style.LogSliderDeadzone = 4;
			style.TabRounding = 4;

			return nullptr;
		}

		ImFont* Dark()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
			style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
			style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
			style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
			style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);  //
			style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
			style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);  //
			style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
			style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);  //
			style.GrabRounding = style.FrameRounding = 2.3f;

			return nullptr;
		}

		inline ImFont* EnemyMouse()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			// EnemyMouse-------------------
			style.Alpha = 1.0f;
			style.DisabledAlpha = 0.6000000238418579f;
			style.WindowPadding = ImVec2(8.0f, 8.0f);
			style.WindowRounding = 3.0f;
			style.WindowBorderSize = 1.0f;
			style.WindowMinSize = ImVec2(32.0f, 32.0f);
			style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
			style.WindowMenuButtonPosition = ImGuiDir_Left;
			style.ChildRounding = 3.0f;
			style.ChildBorderSize = 1.0f;
			style.PopupRounding = 0.0f;
			style.PopupBorderSize = 1.0f;
			style.FramePadding = ImVec2(4.0f, 3.0f);
			style.FrameRounding = 3.0f;
			style.FrameBorderSize = 0.0f;
			style.ItemSpacing = ImVec2(8.0f, 4.0f);
			style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			style.CellPadding = ImVec2(4.0f, 2.0f);
			style.IndentSpacing = 21.0f;
			style.ColumnsMinSpacing = 6.0f;
			style.ScrollbarSize = 14.0f;
			style.ScrollbarRounding = 9.0f;
			style.GrabMinSize = 20.0f;
			style.GrabRounding = 1.0f;
			style.TabRounding = 4.0f;
			style.TabBorderSize = 0.0f;
			// style.TabMinWidthForCloseButton = 0.0f;
			style.ColorButtonPosition = ImGuiDir_Right;
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

			style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_TextDisabled] =
			    ImVec4(0.0f, 0.4000000059604645f, 0.407843142747879f, 1.0f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.1f, 0.1f, 1.0f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1568627506494522f, 0.239215686917305f,
			                                        0.2196078449487686f, 0.6000000238418579f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 1.0f, 0.6499999761581421f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4392156898975372f, 0.800000011920929f,
			                                        0.800000011920929f, 0.1800000071525574f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4392156898975372f, 0.800000011920929f,
			                                               0.800000011920929f, 0.2700000107288361f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4392156898975372f, 0.8078431487083435f,
			                                              0.8588235378265381f, 0.6600000262260437f);
			style.Colors[ImGuiCol_TitleBg] =
			    ImVec4(0.1372549086809158f, 0.1764705926179886f, 0.2078431397676468f, 1.0f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.3f, 0.3f, 1.0f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5400000214576721f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2196078449487686f, 0.2862745225429535f,
			                                            0.2980392277240753f, 0.7099999785423279f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.4399999976158142f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] =
			    ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 1.0f, 1.0f, 0.6800000071525574f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 1.0f, 1.0f, 0.3600000143051147f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.7599999904632568f);
			style.Colors[ImGuiCol_Button] =
			    ImVec4(0.0f, 0.6470588445663452f, 0.6470588445663452f, 0.4600000083446503f);
			style.Colors[ImGuiCol_ButtonHovered] =
			    ImVec4(0.007843137718737125f, 1.0f, 1.0f, 0.4300000071525574f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.6200000047683716f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 1.0f, 1.0f, 0.3300000131130219f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.4199999868869781f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
			style.Colors[ImGuiCol_Separator] =
			    ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.3300000131130219f);
			style.Colors[ImGuiCol_SeparatorHovered] =
			    ImVec4(0.0f, 0.4980392158031464f, 0.4980392158031464f, 0.4699999988079071f);
			style.Colors[ImGuiCol_SeparatorActive] =
			    ImVec4(0.0f, 0.6980392336845398f, 0.6980392336845398f, 1.0f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 1.0f, 1.0f, 0.5400000214576721f);
			style.Colors[ImGuiCol_ResizeGripHovered] =
			    ImVec4(0.0f, 1.0f, 1.0f, 0.7400000095367432f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f,
			                                    0.5764706134796143f, 0.8619999885559082f);
			style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                           0.9764705896377563f, 0.800000011920929f);
			style.Colors[ImGuiCol_TabActive] =
			    ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f,
			                                             0.1450980454683304f, 0.9724000096321106f);
			style.Colors[ImGuiCol_TabUnfocusedActive] =
			    ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			style.Colors[ImGuiCol_TableHeaderBg] =
			    ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
			style.Colors[ImGuiCol_TableBorderStrong] =
			    ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_TableBorderLight] =
			    ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
			style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 1.0f, 1.0f, 0.2199999988079071f);
			style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
			style.Colors[ImGuiCol_NavHighlight] =
			    ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_NavWindowingHighlight] =
			    ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ModalWindowDimBg] =
			    ImVec4(0.03921568766236305f, 0.09803921729326248f, 0.08627451211214066f,
			           0.5099999904632568f);

			return loadCustomFont();
		}

		inline ImFont* Nostromo()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			// Nostromo style from ImThemes
			style.Alpha = 1.0f;
			style.DisabledAlpha = 0.6000000238418579f;
			style.WindowPadding = ImVec2(10.0f, 5.0f);
			style.WindowRounding = 5.0f;
			style.WindowBorderSize = 3.0f;
			style.WindowMinSize = ImVec2(32.0f, 32.0f);
			style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
			style.WindowMenuButtonPosition = ImGuiDir_Left;
			style.ChildRounding = 0.0f;
			style.ChildBorderSize = 3.0f;
			style.PopupRounding = 0.0f;
			style.PopupBorderSize = 1.0f;
			style.FramePadding = ImVec2(6.0f, 3.0f);
			style.FrameRounding = 1.0f;
			style.FrameBorderSize = 0.0f;
			style.ItemSpacing = ImVec2(8.0f, 8.0f);
			style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
			style.CellPadding = ImVec2(2.099999904632568f, 2.0f);
			style.IndentSpacing = 20.0f;
			style.ColumnsMinSpacing = 5.699999809265137f;
			style.ScrollbarSize = 20.0f;
			style.ScrollbarRounding = 0.0f;
			style.GrabMinSize = 10.0f;
			style.GrabRounding = 3.599999904632568f;
			style.TabRounding = 1.0f;
			style.TabBorderSize = 0.0f;
			// style.TabMinWidthForCloseButton = 3.400000095367432f;
			style.ColorButtonPosition = ImGuiDir_Right;
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

			style.Colors[ImGuiCol_Text] =
			    ImVec4(0.4163089990615845f, 1.0f, 0.5716259479522705f, 1.0f);
			style.Colors[ImGuiCol_TextDisabled] =
			    ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.03707932680845261f, 0.0918266698718071f,
			                                         0.1416308879852295f, 0.9399999976158142f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f,
			                                        0.0784313753247261f, 0.9399999976158142f);
			style.Colors[ImGuiCol_Border] =
			    ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.2862745225429535f,
			                                        0.47843137383461f, 0.5400000214576721f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.4000000059604645f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                              0.9764705896377563f, 0.6700000166893005f);
			style.Colors[ImGuiCol_TitleBg] =
			    ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
			style.Colors[ImGuiCol_TitleBgActive] =
			    ImVec4(0.1534380912780762f, 0.4175267517566681f, 0.729613721370697f, 1.0f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
			style.Colors[ImGuiCol_MenuBarBg] =
			    ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f,
			                                            0.01960784383118153f, 0.5299999713897705f);
			style.Colors[ImGuiCol_ScrollbarGrab] =
			    ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] =
			    ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] =
			    ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
			style.Colors[ImGuiCol_CheckMark] =
			    ImVec4(0.8784313797950745f, 0.239215686917305f, 0.239215686917305f, 1.0f);
			style.Colors[ImGuiCol_SliderGrab] =
			    ImVec4(0.8799999952316284f, 0.2400000393390656f, 0.2400000393390656f, 1.0f);
			style.Colors[ImGuiCol_SliderGrabActive] =
			    ImVec4(0.2599999904632568f, 0.5899999737739563f, 0.9800000190734863f, 1.0f);
			style.Colors[ImGuiCol_Button] =
			    ImVec4(0.1029674336314201f, 0.3115374147891998f, 0.557939887046814f, 1.0f);
			style.Colors[ImGuiCol_ButtonHovered] =
			    ImVec4(0.266904890537262f, 0.5975112915039062f, 0.9871244430541992f, 1.0f);
			style.Colors[ImGuiCol_ButtonActive] =
			    ImVec4(0.1392915546894073f, 0.5058678388595581f, 0.8540772199630737f, 1.0f);
			style.Colors[ImGuiCol_Header] =
			    ImVec4(0.06520659476518631f, 0.3304342925548553f, 0.5064377784729004f, 1.0f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                              0.9764705896377563f, 0.800000011920929f);
			style.Colors[ImGuiCol_HeaderActive] =
			    ImVec4(0.2588235437870026f, 0.7269881963729858f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_Separator] =
			    ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
			style.Colors[ImGuiCol_SeparatorHovered] =
			    ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f,
			           0.7799999713897705f);
			style.Colors[ImGuiCol_SeparatorActive] =
			    ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                           0.9764705896377563f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
			style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f,
			                                    0.5764706134796143f, 0.8619999885559082f);
			style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f,
			                                           0.9764705896377563f, 0.800000011920929f);
			style.Colors[ImGuiCol_TabActive] =
			    ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f,
			                                             0.1450980454683304f, 0.9724000096321106f);
			style.Colors[ImGuiCol_TabUnfocusedActive] =
			    ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
			style.Colors[ImGuiCol_PlotLines] =
			    ImVec4(0.3290722370147705f, 1.0f, 0.004291832447052002f, 1.0f);
			style.Colors[ImGuiCol_PlotLinesHovered] =
			    ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogram] =
			    ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
			style.Colors[ImGuiCol_PlotHistogramHovered] =
			    ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
			style.Colors[ImGuiCol_TableHeaderBg] =
			    ImVec4(0.0f, 0.3977376818656921f, 0.545064389705658f, 1.0f);
			style.Colors[ImGuiCol_TableBorderStrong] =
			    ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
			style.Colors[ImGuiCol_TableBorderLight] =
			    ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
			style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
			style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(
			    0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
			style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
			style.Colors[ImGuiCol_NavHighlight] =
			    ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
			style.Colors[ImGuiCol_NavWindowingHighlight] =
			    ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(
			    0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

			return loadCustomFont();
		}

		inline ImFont* VictorSix()
		{
			ImGuiStyle& style = ImGui::GetStyle();

			// Custom----------

			style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.50f, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.10f, 0.05f, 1.00f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.30f, 0.10f, 1.00f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.45f, 0.15f, 1.00f);

			style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.30f, 0.10f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.70f, 0.40f, 1.00f);

			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.6f, 0.85f, 1.00f);

			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 0.50f, 1.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.30f, 0.10f, 1.00f);
			style.Colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.5f, 0.20f, 1.00f);

			return loadCustomFont();
		}
	}  // namespace ImGuiThemes

}  // namespace StrawPen
