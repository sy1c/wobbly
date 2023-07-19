#define MOTL_R PC4
#define MOTL_F PC5
#define MOTL_PWM PD4
#define MOTR_F PC6
#define MOTR_R PC7
#define MOTR_PWM PD5

void motors_init(void);
void motors_left_speed(uint8_t speed);
void motors_right_speed(uint8_t speed);
void motors_set_speed(uint8_t left_speed, uint8_t right_speed);