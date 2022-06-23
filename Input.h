//�Q�l�����̃T���v���R�[�h�A������֐������삷��\��

/**
* @file Input.h
* @brief ���͂Ɋւ���֐��A�萔�̐錾
*/
#ifndef INPUT_H_
#define INPUT_H_



/** @brief �}�E�X�{�^���̎�� */
enum MouseButton
{
	Left,		//!< ��
	Right,		//!< �E
	Center,		//!< �^��
	SideDown,
	SideUp
};

/**
* @brief Input�@�\�������֐�@n
* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s��
* ��InitEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂Ȃ�
* @return ����������(������true)
*/
bool InitInput();

/**
* @brief Input�@�\�I���֐�@n
* Input�@�\���I��������@n
* ��EndEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂Ȃ�
*/
void ReleaseInput();

/**
* @brief ���͏��̍X�V@n
* �f�o�C�X�̓��͏��̍X�V���s��@n
* ���t���[���ɂP�x�K�����s����K�v������
*/
void UpdateInput();

/**
* @brief �{�^����������Ă��邩�̔���֐�
* @retval true�F������Ă���
* @retval false�F������Ă��Ȃ�
* @param[in] button ���肵�����{�^���̎��
*/
bool OnMousePush(MouseButton button_type);

/**
* @brief �{�^���������ꂽ�u�Ԃ̔���֐�
* @retval true�F�������u��
* @retval false�F�������u�Ԃł͂Ȃ�
* @param[in] button ���肵�����{�^���̎��
*/
bool OnMouseDown(MouseButton button_type);

/**
* @brief �{�^���𗣂����u�Ԃ̔���֐�
* @retval true�F�������u��
* @retval false�F�u�Ԃł͂Ȃ�
* @param[in] button ���肵�����{�^���̎��
*/
bool OnMouseUp(MouseButton button_type);


#endif
