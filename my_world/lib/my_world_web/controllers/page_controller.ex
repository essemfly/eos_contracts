defmodule MyWorldWeb.PageController do
  use MyWorldWeb, :controller

  def index(conn, _params) do
    render conn, "index.html"
  end
end
