# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.
use Mix.Config

# General application configuration
config :my_world,
  ecto_repos: [MyWorld.Repo]

# Configures the endpoint
config :my_world, MyWorldWeb.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "JKF5ss+70qRuoMc8BGZg1Lqxye+d+pByKR6GuoxK0BOkcJX2+hJ7c1hFRa5BI32H",
  render_errors: [view: MyWorldWeb.ErrorView, accepts: ~w(html json)],
  pubsub: [name: MyWorld.PubSub,
           adapter: Phoenix.PubSub.PG2]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:user_id]

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env}.exs"
