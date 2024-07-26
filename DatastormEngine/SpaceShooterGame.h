#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"


class SpaceShooterGame : public Window, public InputListener
{
public:
	SpaceShooterGame();
	~SpaceShooterGame();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;


	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
public:
	void render();
	void update();
	void updateModel(Vector3D position, const std::vector<MaterialPtr>& list_material);
	void updateCamera();
	void updateSkyBox();
	void updateLight();

	void drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);

private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	PixelShaderPtr m_sky_ps;
	ConstantBufferPtr m_cb;
	ConstantBufferPtr m_sky_cb;
	TexturePtr m_wall_tex;
	TexturePtr m_earth_color_tex;
	TexturePtr m_earth_spec_tex;
	TexturePtr m_earth_night_tex;
	TexturePtr m_clouds_tex;
	TexturePtr m_terrain_tex;
	TexturePtr m_barrel_tex;
	TexturePtr m_brick_tex;
	TexturePtr m_windows_tex;
	TexturePtr m_wood_tex;

	TexturePtr m_sky_tex;
	MeshPtr m_mesh;
	MeshPtr m_sky_mesh;
	MeshPtr m_plane_mesh;
	MeshPtr m_terrain_mesh;
	MeshPtr m_house_mesh;

	MaterialPtr m_mat;
	MaterialPtr m_brick_mat;
	MaterialPtr m_earth_mat;
	MaterialPtr m_sky_mat;
	MaterialPtr m_terrain_mat;
	MaterialPtr m_barrel_mat;
	MaterialPtr m_wood_mat;
	MaterialPtr m_window_mat;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_light_rot_y = 0.0f;


	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	bool cull = true;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	float m_time = 0.0f;
	float m_light_radius = 500.0f;
	float m_attenuation = 2.0f;
	bool m_anim = false;

	bool m_play_state = false;
	bool m_fullscreen_state = false;

	std::vector<MaterialPtr> m_material_list;

	Vector4D m_light_position;
};