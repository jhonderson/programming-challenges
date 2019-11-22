require_relative 'node'

class Graph

  attr_reader :nodes

  def initialize
    @nodes = {}
  end

  def add_node(p_node)
    @nodes[p_node.name] = p_node
  end

  def add_edge(p_predecessor_name, p_successor_name)
    @nodes[p_predecessor_name] ||= Node.new(p_predecessor_name)
    @nodes[p_successor_name] ||= Node.new(p_successor_name)
    @nodes[p_predecessor_name].add_edge(@nodes[p_successor_name])
  end

  def [](p_name)
    @nodes[p_name]
  end

  def clone
    new_graph = Graph.new
    @nodes.each do |k,v|
      v.successors.each {|node| new_graph.add_edge(k, node.name) }
    end
    new_graph
  end

end