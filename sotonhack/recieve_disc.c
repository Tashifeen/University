#include <concord/discord.h>
#include <stdio.h>
#include <string.h>
#define GUILD_ID 1482366885482987655

void on_ready(struct discord *client, const struct discord_ready *event) {}

void on_interaction(struct discord *client,
                    const struct discord_interaction *event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
    return; /* return if interaction isn't a slash command */
}

void receive_data(struct discord *client, const struct discord_message *event) {
  struct discord_create_message params = {.content = "recieved"};
  discord_create_message(client, event->channel_id, &params, NULL);
      FILE* f = fopen("./out.txt","a");
      fprintf(f,"%s\n",event->content);
      fclose(f);
}

int main(void) {
  struct discord *client = discord_config_init("./config.json");
  if (client == NULL) {
    printf("%s", "Failed to init");
    return 1;
  }

  discord_set_on_ready(client, &on_ready);
  discord_set_on_interaction_create(client, &on_interaction);
  discord_set_on_command(client, "data", &receive_data);
  discord_run(client);

  return 0;
