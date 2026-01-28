#ifndef CONFIG_H
#define CONFIG_H

int config_load(const char *path);
const char *config_get_data_dir(void);
const char *config_get_db_name(void);
void config_free(void);


#endif