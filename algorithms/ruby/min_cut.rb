require_relative 'node'
require_relative 'graph'

def selec_random_edge(p_graph)
	keys = p_graph.nodes.keys
	random_key = keys[rand(keys.length)]
	random_node = p_graph.nodes[random_key]
	return random_key, rand(random_node.successors.length)
end

def contract_vertices(p_graph, p_u_key, p_v_key)
  u_node = p_graph.nodes[p_u_key]
  v_node = u_node.successors[p_v_key]

  (u_node.successors << v_node.successors).flatten!
  u_node.successors.delete_if {|node| (node.name ==  u_node.name || node.name ==  v_node.name) }
  p_graph.nodes.each { |k,v| v.successors.map! { |node| node.name == v_node.name ? u_node : node }}
  p_graph.nodes.delete(v_node.name)
end

def print_graph(p_graph)
  puts "G(n=#{p_graph.nodes.length})------------------------"
  p_graph.nodes.each do |k,v|
    puts v
  end
  puts "------------------------"
end

def min_cut(p_graph)
  until p_graph.nodes.size <= 2
    u_key, v_key = selec_random_edge(p_graph)
    contract_vertices(p_graph, u_key, v_key)
  end
  return p_graph[p_graph.nodes.keys[0]].successors.length
end