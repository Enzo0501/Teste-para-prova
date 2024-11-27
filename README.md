# Teste-para-prova
-------------------------------------------
using Lista.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/lista/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/lista/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/lista/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/lista/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/lista/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.Run();

+++++++

using Microsoft.EntityFrameworkCore;

namespace Lista.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}

++++++++++++++

namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}


--------------------------------------------------------
###Relacionamento entre tabelas### 

DB -

Um pra um
protected override void OnModelCreating(ModelBuilder modelBuilder)
{
    modelBuilder.Entity<Tabela2>()
        .HasOne(t => t.Tarefa)
        .WithOne()
        .HasForeignKey<Tabela2>(t => t.TarefaId);
}

protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configuração do relacionamento um-para-muitos
            modelBuilder.Entity<Tabela2>()
                .HasOne(t => t.Tarefa)           // Uma Tabela2 tem uma Tarefa
                .WithMany(t => t.Tabela2s)       // Uma Tarefa tem muitas Tabela2
                .HasForeignKey(t => t.TarefaId); // A Foreign Key é TarefaId
        }

--------------------------------------------------
Criar uma Solution e API

dotnet new sln --output NomeDaSolução ->cd .\NomeSoluçao\

dotnet new web --name NomedaAPI
dentro da solucao
dotnet sln add NomedaAPI

dotnet run --project NomeApi
pegar http://localhost:5258
criar teste.http

criar pasta models
---
namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}
---
Dentro da API
dotnet add package Microsoft.EntityFrameworkCore.Sqlite
dotnet add package Microsoft.EntityFrameworkCore.Design


dotnet ef migrations add InitialCreate
dotnet ef database update

###Criando Um react####
npx create-react-app my-app --template typescript
cd my-app
npm install axios


my-app
├── node_modules
├── public
│   └── index.html
├── src
│   ├── App.tsx
│   ├── index.css
│   ├── index.tsx
│   └── react-app-env.d.ts
├── package.json
├── tsconfig.json
└── README.md

npm install react-router-dom
npm install @types/react-router-dom

--------------------

using APITeste.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/apiteste/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/apiteste/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/apiteste/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.MapPut("/apiteste/tarefas/alterar/{id}", ([FromRoute] int id,
    [FromBody] Tarefa tarefaAlterada, 
    [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    tarefa.Nome = tarefaAlterada.Nome;
    ctx.Tarefas.Update(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});


app.Run();

--------

using Microsoft.EntityFrameworkCore;

namespace APITeste.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}
-------
namespace APITeste.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}

--------------------------------------------------------
Relacionamentos
UM pra muitos

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        public ICollection<Tarefa> Tarefas { get; set; } = new List<Tarefa>();
    }
}

--

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;
        
        // Propriedade de chave estrangeira
        public int UsuarioId { get; set; }
        public Usuario Usuario { get; set; }
    }
}

--
namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Tarefa> Tarefas { get; set; }
        public DbSet<Usuario> Usuarios { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Tarefa>()
                .HasOne(t => t.Usuario)
                .WithMany(u => u.Tarefas)
                .HasForeignKey(t => t.UsuarioId);
        }
    }
}

--
app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    var usuario = ctx.Usuarios.Find(tarefa.UsuarioId);
    if (usuario == null)
    {
        return Results.BadRequest("Usuário não encontrado.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

----

####Muitos pra muitos:

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        
        // Relacionamento muitos-para-muitos
        public ICollection<Tarefa> Tarefas { get; set; } = new List<Tarefa>();
    }
}

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;

        // Relacionamento muitos-para-muitos
        public ICollection<Usuario> Usuarios { get; set; } = new List<Usuario>();
    }
}


--
namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Tarefa> Tarefas { get; set; }
        public DbSet<Usuario> Usuarios { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // O EF Core já reconhece automaticamente o relacionamento muitos-para-muitos
            modelBuilder.Entity<Usuario>()
                .HasMany(u => u.Tarefas)
                .WithMany(t => t.Usuarios);
        }
    }
}

Exemplo de API para cadastrar uma tarefa com múltiplos usuários
Aqui está um exemplo de como você poderia cadastrar uma tarefa e associar vários usuários a ela:

csharp
Copiar código
app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (tarefa.Usuarios == null || !tarefa.Usuarios.Any())
    {
        return Results.BadRequest("É necessário associar pelo menos um usuário à tarefa.");
    }

    foreach (var usuario in tarefa.Usuarios)
    {
        var usuarioExistente = ctx.Usuarios.Find(usuario.UsuarioId);
        if (usuarioExistente == null)
        {
            return Results.BadRequest($"Usuário com ID {usuario.UsuarioId} não encontrado.");
        }
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

Exemplo de API para buscar tarefas com seus usuários
csharp
Copiar código
app.MapGet("/apiteste/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.Include(t => t.Usuarios).ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

Exemplo de API para buscar usuários com suas tarefas
csharp
Copiar código
app.MapGet("/apiteste/usuarios/listar", ([FromServices] AppDataContext ctx) => 
{
    var usuarios = ctx.Usuarios.Include(u => u.Tarefas).ToList();
    if (usuarios.Any())
    {
        return Results.Ok(usuarios);
    }
    return Results.NotFound("Nenhum usuário encontrado.");
});

-------

###Um pra um###

namespace APITeste.Models
{
    public class Usuario
    {
        public int UsuarioId { get; set; }
        public string? Nome { get; set; }
        
        // Relacionamento um-para-um com Tarefa
        public Tarefa? Tarefa { get; set; }
    }
}

namespace APITeste.Models
{
    public class Tarefa
    {
        public int TarefaId { get; set; }
        public string? Nome { get; set; }
        public DateTime CriadoEm { get; set; } = DateTime.Now;

        // Chave estrangeira para garantir relacionamento um-para-um
        public int UsuarioId { get; set; }
        public Usuario Usuario { get; set; }
    }
}

using Microsoft.EntityFrameworkCore;

namespace APITeste.Models
{
    public class AppDataContext : DbContext
    {
        public DbSet<Usuario> Usuarios { get; set; }
        public DbSet<Tarefa> Tarefas { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=app.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configurar relacionamento um-para-um entre Usuario e Tarefa
            modelBuilder.Entity<Usuario>()
                .HasOne(u => u.Tarefa)
                .WithOne(t => t.Usuario)
                .HasForeignKey<Tarefa>(t => t.UsuarioId);  // Tarefa terá a chave estrangeira UsuarioId
        }
    }
}

app.MapPost("/apiteste/usuarios/cadastrar", ([FromBody] Usuario usuario, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(usuario.Nome))
    {
        return Results.BadRequest("O nome do usuário é obrigatório.");
    }

    if (usuario.Tarefa == null)
    {
        return Results.BadRequest("É necessário fornecer uma tarefa.");
    }

    ctx.Usuarios.Add(usuario);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/usuarios/buscar/{usuario.UsuarioId}", usuario);
});

app.MapGet("/apiteste/usuarios/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var usuario = ctx.Usuarios
        .Include(u => u.Tarefa)  // Inclui a tarefa associada ao usuário
        .FirstOrDefault(u => u.UsuarioId == id);

    if (usuario == null)
    {
        return Results.NotFound("Usuário não encontrado.");
    }

    return Results.Ok(usuario);
});


----------------------------------------------------------------------------


using Microsoft.EntityFrameworkCore;

namespace API.Models;

//Implementar a herança da classe DbContext
public class AppDataContext : DbContext
{
    //Informar quais as classes serão tabelas no banco de dados
    public DbSet<Produto> Produtos { get; set; }
    public DbSet<Categoria> Categorias { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=Ecommerce.db");
    }

}

---

using System;

namespace API.Models;

public class Categoria
{
    public int CategoriaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;

}

-----

namespace API.Models;

public class Produto
{
    //C# - Contrutor da classe
    public Produto()
    {
        Id = Guid.NewGuid().ToString();
        CriadoEm = DateTime.Now;
    }
    //C# - Atributo com get e set
    public string? Id { get; set; }
    public string? Nome { get; set; }
    public string? Descricao { get; set; }
    public double Preco { get; set; }
    public int Quantidade { get; set; }
    public DateTime CriadoEm { get; set; }
    public Categoria Categoria { get; set; }
    public int CategoriaId { get; set; }

}


------

using API.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();

builder.Services.AddCors(options =>
    options.AddPolicy("Acesso Total",
        configs => configs
            .AllowAnyOrigin()
            .AllowAnyHeader()
            .AllowAnyMethod())
);

var app = builder.Build();

app.UseCors("Acesso total");


app.MapGet("/", () => "API de Produtos");

//GET: /api/categoria/listar
app.MapGet("/api/categoria/listar", ([FromServices] AppDataContext ctx) =>
{
    if (ctx.Categorias.Any())
    {
        return Results.Ok(ctx.Categorias.ToList());
    }
    return Results.NotFound();
});

//POST: /api/categoria/cadastrar
app.MapPost("/api/categoria/cadastrar", ([FromBody] Categoria categoria,
    [FromServices] AppDataContext ctx) =>
{
    ctx.Categorias.Add(categoria);
    ctx.SaveChanges();
    return Results.Created("", categoria);
});

//GET: /api/produto/listar
app.MapGet("/api/produto/listar", ([FromServices] AppDataContext ctx) =>
{

    if (ctx.Produtos.Any())
    {
        return Results.Ok(ctx.Produtos.Include(x => x.Categoria).ToList());
    }
    return Results.NotFound();
});

//GET: /api/produto/buscar/{id}
app.MapGet("/api/produto/buscar/{id}", ([FromRoute] string id,
    [FromServices] AppDataContext ctx) =>
{
    //Expressão lambda em C#
    // Produto? produto = ctx.Produtos.FirstOrDefault(x => x.Nome == "Variável com o nome do produto");
    // List<Produto> lista = ctx.Produtos.Where(x => x.Quantidade > 10).ToList();
    Produto? produto = ctx.Produtos.Find(id);
    if (produto == null)
    {
        return Results.NotFound();
    }
    return Results.Ok(produto);
});

//POST: /api/produto/cadastrar
app.MapPost("/api/produto/cadastrar", ([FromBody] Produto produto,
    [FromServices] AppDataContext ctx) =>
{
    Categoria? categoria = ctx.Categorias.Find(produto.CategoriaId);
    if (categoria is null)
    {
        return Results.NotFound();
    }
    produto.Categoria = categoria;
    ctx.Produtos.Add(produto);
    ctx.SaveChanges();
    return Results.Created("", produto);
});

//DELETE: /api/produto/deletar/{id}
app.MapDelete("/api/produto/deletar/{id}", ([FromRoute] string id,
    [FromServices] AppDataContext ctx) =>
{
    Produto? produto = ctx.Produtos.Find(id);
    if (produto == null)
    {
        return Results.NotFound();
    }
    ctx.Produtos.Remove(produto);
    ctx.SaveChanges();
    return Results.Ok(produto);
});

//PUT: /api/produto/alterar/{id}
//PUT: /api/produto/alterar/{id}
app.MapPut("/api/produto/alterar/{id}", ([FromRoute] string id,
    [FromBody] Produto produtoAlterado,
    [FromServices] AppDataContext ctx) =>
{
    Produto? produto = ctx.Produtos.Find(id);
    if (produto == null)
    {
        return Results.NotFound();
    }

    Categoria? categoria = ctx.Categorias.Find(produtoAlterado.CategoriaId);
    if (categoria is null)
    {
        return Results.NotFound();
    }

    // Atualizar os campos
    produto.Nome = produtoAlterado.Nome;
    produto.Descricao = produtoAlterado.Descricao;
    produto.Quantidade = produtoAlterado.Quantidade;
    produto.Preco = produtoAlterado.Preco;
    produto.Categoria = categoria;

    // Salvar alterações
    ctx.Produtos.Update(produto);
    ctx.SaveChanges();

    return Results.Ok(produto);
});


app.UseCors("Acesso Total");

app.Run();

----------------

### Requisação para a raiz da aplicação
GET http://localhost:5217

### Listar categorias
GET http://localhost:5217/api/categoria/listar

### Cadastrar categoria
POST http://localhost:5217/api/categoria/cadastrar
Content-Type: application/json

{
    "nome" : "Celular"
}

-------

GET http://localhost:5217

### Listar produtos
GET http://localhost:5217/api/produto/listar

### Buscar produto
GET http://localhost:5217/api/produto/buscar/054bacf4-aa7f-406c-99e6-30c580524d32

### Cadastrar produto
POST http://localhost:5217/api/produto/cadastrar
Content-Type: application/json

{
    "nome" : "Hotwheels",
    "preco" : 20,
    "quantidade" : 1,
    "descricao" : "Carrinho",
    "categoriaId" : 1
}

### Deletar produto
DELETE http://localhost:5217/api/produto/deletar/d9f79f87-2909-4f54-b901-7cd995c03eb9

### Alterar produto
PUT http://localhost:5217/api/produto/alterar/054bacf4-aa7f-406c-99e6-30c580524d32
Content-Type: application/json

{
    "nome" : "Nintendo",
    "descricao" : "Switch",
    "preco" : 1300,
    "quantidade" : 1,
    "categoriaId" : 2    
}

----------------------------------------------------

ProdutoAlterar.tsx

import axios from "axios";
import { useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import { Produto } from "../../../models/Produto";
import { Categoria } from "../../../models/Categoria";

function ProdutoAlterar() {
  const { id } = useParams();
  const [categorias, setCategorias] = useState<Categoria[]>([]);
  const [nome, setNome] = useState("");
  const [descricao, setDescricao] = useState("");
  const [quantidade, setQuantidade] = useState(0);
  const [preco, setPreco] = useState(0);
  const [categoriaId, setCategoriaId] = useState(0);

  useEffect(() => {
    if (id) {
      axios
        .get<Produto>(`http://localhost:5217/api/produto/buscar/${id}`)
        .then((resposta) => {
          const produto = resposta.data;
          setNome(produto.nome);
          setDescricao(produto.descricao);
          setQuantidade(produto.quantidade);
          setPreco(produto.preco);
          setCategoriaId(produto.categoriaId); // Definir o categoriaId corretamente
          buscarCategorias();
        });
    }
  }, [id]);

  function buscarCategorias() {
    axios
      .get<Categoria[]>("http://localhost:5217/api/categoria/listar")
      .then((resposta) => {
        setCategorias(resposta.data);
      });
  }

  function enviarProduto(e: any) {
    e.preventDefault();

    if (!categoriaId) {
      alert("Selecione uma categoria válida.");
      return;
    }

    const produto: Produto = {
      nome: nome,
      descricao: descricao,
      quantidade: Number(quantidade),
      preco: Number(preco),
      categoriaId: categoriaId,
    };

    axios
      .put(`http://localhost:5217/api/produto/alterar/${id}`, produto)
      .then((resposta) => {
        console.log(resposta.data);
        alert("Produto alterado com sucesso!");
      })
      .catch((erro) => {
        console.error(erro);
        alert("Erro ao alterar o produto.");
      });
  }

  return (
    <div id="alterar-produto" className="container">
      <h1>Alterar Produto</h1>
      <form onSubmit={enviarProduto}>
        <div>
          <label htmlFor="nome">Nome</label>
          <input
            type="text"
            id="nome"
            name="nome"
            value={nome}
            required
            onChange={(e: any) => setNome(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="descricao">Descrição</label>
          <input
            type="text"
            id="descricao"
            value={descricao}
            name="descricao"
            onChange={(e: any) => setDescricao(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="preco">Preço</label>
          <input
            type="number"
            id="preco"
            value={preco}
            name="preco"
            min="0.01"
            step="0.01"
            required
            onChange={(e: any) => setPreco(Number(e.target.value))}
          />
        </div>

        <div>
          <label htmlFor="quantidade">Quantidade</label>
          <input
            type="number"
            id="quantidade"
            value={quantidade}
            name="quantidade"
            min="0"
            required
            onChange={(e: any) => setQuantidade(Number(e.target.value))}
          />
        </div>

        <div>
          <label htmlFor="categoriaId">Categoria</label>
          <select
            value={categoriaId} // Define o valor selecionado com base no estado
            onChange={(e: any) => setCategoriaId(Number(e.target.value))}
            required
          >
            <option value={0} disabled>
              Selecione uma categoria
            </option>
            {categorias.map((categoria) => (
              <option value={categoria.categoriaId} key={categoria.categoriaId}>
                {categoria.nome}
              </option>
            ))}
          </select>
        </div>

        <button type="submit">Alterar Produto</button>
      </form>
    </div>
  );
}

export default ProdutoAlterar;
--------------------------------------

ProdutoCadastro:

import { useEffect, useState } from "react";
import { Produto } from "../../../models/Produto";
import { Categoria } from "../../../models/Categoria";
import axios from "axios";

function ProdutoCadastro() {
  const [categorias, setCategorias] = useState<Categoria[]>([]);
  const [nome, setNome] = useState("");
  const [descricao, setDescricao] = useState("");
  const [quantidade, setQuantidade] = useState("");
  const [preco, setPreco] = useState("");
  const [categoriaId, setCategoriaId] = useState(0);

  // Ajustando o useEffect para carregar as categorias corretamente
  useEffect(() => {
    axios
      .get<Categoria[]>("http://localhost:5217/api/categoria/listar")
      .then((resposta) => {
        setCategorias(resposta.data);
      })
      .catch((erro) => {
        console.error("Erro ao carregar categorias:", erro);
      });
  }, []); // O useEffect agora é chamado apenas uma vez, na montagem do componente

  function enviarProduto(e: any) {
    e.preventDefault();

    // Verificação simples para garantir que todos os campos obrigatórios estão preenchidos
    if (!nome || !descricao || !quantidade || !preco || !categoriaId) {
      alert("Todos os campos são obrigatórios.");
      return;
    }

    const produto: Produto = {
      nome: nome,
      descricao: descricao,
      quantidade: Number(quantidade),
      preco: Number(preco),
      categoriaId: categoriaId,
    };

    fetch("http://localhost:5217/api/produto/cadastrar", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(produto),
    })
      .then((resposta) => {
        if (!resposta.ok) {
          throw new Error("Erro ao cadastrar produto.");
        }
        return resposta.json();
      })
      .then((produto) => {
        console.log("Produto cadastrado com sucesso:", produto);
        alert("Produto cadastrado com sucesso!");
      })
      .catch((erro) => {
        console.error("Erro ao cadastrar produto:", erro);
        alert("Erro ao cadastrar o produto.");
      });
  }

  return (
    <div id="cadastrar_produto" className="container">
      <h1>Cadastrar Produto</h1>
      <form onSubmit={enviarProduto}>
        <div>
          <label htmlFor="nome">Nome</label>
          <input
            type="text"
            id="nome"
            name="nome"
            required
            onChange={(e) => setNome(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="descricao">Descrição</label>
          <input
            type="text"
            id="descricao"
            name="descricao"
            onChange={(e) => setDescricao(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="preco">Preço</label>
          <input
            type="number"
            id="preco"
            name="preco"
            onChange={(e) => setPreco(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="quantidade">Quantidade</label>
          <input
            type="number"
            id="quantidade"
            name="quantidade"
            onChange={(e) => setQuantidade(e.target.value)}
          />
        </div>

        <div>
          <label htmlFor="categoriaId">Categoria</label>
          <select
            id="categoriaId"
            name="categoriaId"
            onChange={(e) => setCategoriaId(Number(e.target.value))}
            value={categoriaId}
          >
            <option value="">Selecione uma categoria</option>
            {categorias.map((categoria) => (
              <option
                value={categoria.categoriaId}
                key={categoria.categoriaId}
              >
                {categoria.nome}
              </option>
            ))}
          </select>
        </div>

        <button type="submit">Cadastrar Produto</button>
      </form>
    </div>
  );
}

export default ProdutoCadastro;

-------------------------------------------------
Produto Lista:

import { useEffect, useState } from "react";
import { Produto } from "../../../models/Produto";
import styles from "./ProdutoLista.module.css";
import axios from "axios";
import { Link } from "react-router-dom";

function ProdutoLista() {
  const [produtos, setProdutos] = useState<Produto[]>([]);

  useEffect(() => {
    fetch("http://localhost:5217/api/produto/listar")
      .then((resposta) => {
        return resposta.json();
      })
      .then((produtos) => {
        setProdutos(produtos);
      });
  });

  function deletar(id: string) {
    axios
      .delete(`http://localhost:5217/api/produto/deletar/${id}`)
      .then((resposta) => {
        console.log(resposta.data);
      });
  }

  return (
    <div className="container">
      <h1>Lista de Produtos</h1>
      <table className={styles.table}>
        <thead>
          <tr>
            <th>#</th>
            <th>Nome</th>
            <th>Categoria</th>
            <th>Criado Em</th>
            <th>Deletar</th>
            <th>Alterar</th>
          </tr>
        </thead>
        <tbody>
          {produtos.map((produto) => (
            <tr key={produto.id}>
              <td>{produto.id}</td>
              <td>{produto.nome}</td>
              <td>{produto.categoria?.nome}</td>
              <td>{produto.criadoEm}</td>
              <td>
                <button onClick={() => deletar(produto.id!)}>
                  Deletar
                </button>
              </td>
              <td>
                <Link to={`/pages/produto/alterar/${produto.id}`}>
                  Alterar
                </Link>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default ProdutoLista;

------------------------------------------------------------
ProdutoLista.modules.css

/* ProductTable.module.css */

h1 {
  text-align: center;
  color: #333;
  margin-bottom: 8px;
}

table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 16px;
  font-family: Arial, sans-serif;
}

thead {
  background-color: #007bff;
  color: #fff;
}

th,
td {
  padding: 12px 16px;
  border: 1px solid #ddd;
  text-align: left;
}

tbody tr:nth-child(even) {
  background-color: #f2f2f2;
}

tbody tr:hover {
  background-color: #e9f4ff;
}

th {
  font-weight: bold;
  text-transform: uppercase;
}

td {
  color: #555;
}

-------------------------------
Categoria.ts

export interface Categoria {
  categoriaId?: number;
  nome: string;
  criadoEm?: string;
}

---------------------------
Produto.ts

import { Categoria } from "./Categoria";

export interface Produto {
  id?: string;
  nome: string;
  descricao: string;
  preco: number;
  quantidade: number;
  criadoEm?: string;
  categoriaId: number;
  categoria?: Categoria;
}

-------
App.tsx:

import React from "react";
import ConsultarCEP from "./components/samples/ConsultarCEP";
import ProdutoLista from "./components/pages/produto/ProdutoLista";
import ProdutoCadastro from "./components/pages/produto/ProdutoCadastro";
import { BrowserRouter, Link, Route, Routes } from "react-router-dom";
import ProdutoAlterar from "./components/pages/produto/ProdutoAlterar";

function App() {
  return (
    <div id="app">
      <BrowserRouter>
        <nav>
          <ul>
            <li>
              <Link to="/">Home</Link>
            </li>
            <li>
              <Link to="/pages/produto/listar">Listar Produtos</Link>
            </li>
            <li>
              <Link to="/pages/produto/cadastrar">
                Cadastrar Produto
              </Link>
            </li>
            <li>
              <Link to="/pages/endereco/consultar">
                Consultar Endereço
              </Link>
            </li>
          </ul>
        </nav>
        <Routes>
          <Route path="/" element={<ProdutoLista />} />
          <Route
            path="/pages/produto/listar"
            element={<ProdutoLista />}
          />
          <Route
            path="/pages/produto/cadastrar"
            element={<ProdutoCadastro />}
          />
          <Route
            path="/pages/endereco/consultar"
            element={<ConsultarCEP />}
          />
          <Route
            path="/pages/produto/alterar/:id"
            element={<ProdutoAlterar />}
          />
        </Routes>
      </BrowserRouter>
    </div>
  );
}

export default App;

---------------------

index.tsx

import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App";
import "./styles.css";

const root = ReactDOM.createRoot(document.getElementById("root") as HTMLElement);
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);

-----------------
styles.css

/* Reset básico */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
  }
  
  /* Fonte padrão da aplicação */
  body {
    font-family: Arial, sans-serif;
    background-color: #f9f9f9;
    color: #333;
  }
  
  /* Estilos globais para containers */
  .container {
    width: 90%;
    max-width: 1200px;
    margin: 0 auto;
    padding: 16px;
  
    /* Centralizando com flexbox */
    display: flex;
    flex-direction: column;
    align-items: center; /* Alinhamento horizontal */
    min-height: 100vh; /* Garante que o conteúdo ocupe a altura total da tela */
  }
  
  /* Barra de navegação */
  nav {
    background-color: #007bff;
    padding: 16px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
  }
  
  nav ul {
    list-style-type: none;
    display: flex;
    justify-content: space-around;
    margin: 0;
    padding: 0;
  }
  
  nav li {
    margin: 0 10px;
  }
  
  nav a {
    color: white;
    text-decoration: none;
    font-weight: bold;
    padding: 8px 16px;
    border-radius: 4px;
    transition: background-color 0.3s ease;
  }
  
  nav a:hover {
    background-color: #0056b3;
  }
  
  /* Estilos de responsividade */
  @media (max-width: 768px) {
    nav ul {
      flex-direction: column;
      align-items: center;
    }
  
    nav li {
      margin: 5px 0;
    }
  }






